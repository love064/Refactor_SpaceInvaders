#include "LeaderBoard.h"
#include <vector>
#include <chrono>
#include <fstream>
#include <string>

GameState LeaderBoard::update(int score) {
	if (newHighScore) {
		yourScore.score = score;
		SetName();
	}
	if (IsKeyReleased(KEY_SPACE) && !newHighScore) {
		return GameState::STARTSCREEN;
	}
	return GameState::ENDSCREEN;
}

void LeaderBoard::SetName() {
	if (const int key = GetCharPressed(); key >= 32 && key <= 125 && letterCount < MAX_LETTER_COUNT) {
		name += static_cast<char>(key); //TODO: fix this (gsl::narrow_cast<char>(key)) find out how to include gsl
		letterCount++;
	}

	if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0) {
		name.pop_back();
		letterCount--;
	}

	if (letterCount > 0 && letterCount < MAX_LETTER_COUNT && IsKeyReleased(KEY_ENTER)) {
		yourScore.name = name;
		ReadFromFile("Assets/LeaderBoard.txt");
		SortLeaderBoard();
		newHighScore = false;
	}
}

void LeaderBoard::ReadFromFile(std::string_view fileName) {
	std::ifstream LeaderBoardFile(fileName.data(), std::ios::in | std::ios::binary);
	if (LeaderBoardFile.is_open()) { 
		for (int i = 0; i < 5; i++) { 
			ReadPlayerData(LeaderBoardFile);
		}
	}
}

void LeaderBoard::ReadPlayerData(std::ifstream& LeaderBoardFile) {
	std::string line;
	PlayerData currentPlayer;

	while (std::getline(LeaderBoardFile, line)) {
		if (line.contains("Player Name:")) {
			currentPlayer.name = line.substr(13);
		}
		else if (line.contains("Score:")) {
			std::istringstream(line.substr(7)) >> currentPlayer.score;
			Leaderboard.push_back(currentPlayer);
		}
	}
}

void LeaderBoard::SortLeaderBoard() { 
	auto toChange = std::ranges::find_if(Leaderboard, [this](const PlayerData& player) {
		return yourScore.score > player.score;
	});
	if (toChange != Leaderboard.end()) {
		Leaderboard.insert(toChange, yourScore);
		Leaderboard.pop_back();
	}
}

void LeaderBoard::WriteToFile(std::string_view fileName) const {
	std::ofstream LeaderBoardFile(fileName.data(), std::ios::out | std::ios::binary);
	if (LeaderBoardFile.is_open()){
		for (const auto& var : Leaderboard) {
			LeaderBoardFile << "Player Name: " << var.name << "\n";
			LeaderBoardFile << "Score: " << var.score << "\n";
		}
	}
}

void LeaderBoard::reset() {
	WriteToFile("Assets/LeaderBoard.txt");
	Leaderboard.clear();
	yourScore = { "", 0};
	name = "";
	letterCount = 0;
	newHighScore = true;
}

void LeaderBoard::render() const noexcept {
	if (newHighScore) {
		SetNameRender();
	}
	else {
		HSRender();
	}
}

void LeaderBoard::SetNameRender() const noexcept{
	DrawText("NEW HIGHSCORE!", X_RENDER_INDENT, Y_RENDER_INDENT, FONT_SIZE_LARGE, YELLOW);
	DrawText("ENTER NAME!", X_RENDER_INDENT, Y_RENDER_INDENT * 2, FONT_SIZE_SMALL, YELLOW);
	DrawRectangleRec(NAME_TEXTBOX, LIGHTGRAY);
	DrawRectangleLinesEx(NAME_TEXTBOX, LINE_THICKNESS, RED);
	DrawText(name.data(), getTextboxXI() + NAME_OFFSET_X, getTextboxYI() + NAME_OFFSET_Y, FONT_SIZE_MEDIUM, MAROON);
	DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_LETTER_COUNT - 1), X_RENDER_INDENT, Y_RENDER_INDENT * 3, FONT_SIZE_SMALL, YELLOW);

	if (letterCount > 0 && letterCount < MAX_LETTER_COUNT){
		DrawText("PRESS ENTER TO CONTINUE", X_RENDER_INDENT, Y_RENDER_INDENT * 4, FONT_SIZE_MEDIUM, YELLOW);
	}
}

void LeaderBoard::HSRender() const noexcept{
	DrawText("PRESS SPACE TO CONTINUE", X_RENDER_INDENT, Y_RENDER_INDENT, FONT_SIZE_MEDIUM, YELLOW);
	DrawText("LEADERBOARD", LEADERBOARD_X_OFFSET, LEADERBOARD_Y_OFFSET - FONT_SIZE_MEDIUM, FONT_SIZE_MEDIUM, YELLOW);

	int i = 0;
	for (const auto& var : Leaderboard) {
		DrawText(var.name.data(), LEADERBOARD_X_OFFSET, LEADERBOARD_Y_OFFSET + (i * FONT_SIZE_MEDIUM), FONT_SIZE_MEDIUM, YELLOW);
		DrawText(TextFormat("%i", var.score), LEADERBOARD_SCORE_X_OFFSEET, LEADERBOARD_Y_OFFSET + (i * FONT_SIZE_MEDIUM), FONT_SIZE_MEDIUM, YELLOW);
		i++;
	}
}

int LeaderBoard::getTextboxXI() const noexcept {
	return static_cast<int>(NAME_TEXTBOX.x);
}
int LeaderBoard::getTextboxYI() const noexcept {
	return static_cast<int>(NAME_TEXTBOX.y);
}
