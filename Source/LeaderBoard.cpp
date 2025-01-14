#include "LeaderBoard.h"
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include "Util.h"
#include <algorithm>
#include <iostream>

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
	if (const int key = GetCharPressed(); key >= 32 && key <= 125 && letterCount < MAX_LETTER_COUNT){
#pragma warning(push)
#pragma warning(disable: 26472) // Aware of narrowing conversion, but it should be safe as key(int) is within bounds of char (if statment above)
		name += static_cast<char>(key);
#pragma warning(pop)
		letterCount++;
	}

	if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0) {
		name.pop_back();
		letterCount--;
	}

	if (letterCount > 0 && letterCount < MAX_LETTER_COUNT && IsKeyReleased(KEY_ENTER)) {
		yourScore.name = name;
		ReadFromFile(HS_FILE_NAME);
		SortLeaderBoard();
		newHighScore = false;
	}
}

void LeaderBoard::ReadFromFile(std::string_view fileName) {
	std::ifstream LeaderBoardFile(fileName.data(), std::ios::in | std::ios::binary);
	if (LeaderBoardFile.is_open()) { 
		for (int i = 0; i < LEADERBOARD_COUNT; i++) { 
			ReadPlayerData(LeaderBoardFile);
		}
	}
}

void LeaderBoard::ReadPlayerData(std::ifstream& LeaderBoardFile) {
	std::string line;
	PlayerData currentPlayer;

	while (std::getline(LeaderBoardFile, line)) {
		if (line.contains(PLAYER_NAME_TEXT)) { 
			currentPlayer.name = line.substr(PLAYER_NAME_TEXT.size());
		}
		else if (line.contains(PLAYER_SCORE_TEXT)) {
			std::istringstream(line.substr(PLAYER_SCORE_TEXT.size())) >> currentPlayer.score;
			highscores.push_back(currentPlayer);
		}
	}
}

void LeaderBoard::SortLeaderBoard() {
	highscores.push_back(yourScore);
	std::sort(highscores.begin(), highscores.end(), [](const PlayerData& player1, const PlayerData& player2)
		{
			return player2.score < player1.score;
	});
	highscores.pop_back();
}

void LeaderBoard::WriteToFile(std::string_view fileName) const {
	std::ofstream LeaderBoardFile(fileName.data(), std::ios::out | std::ios::binary);
	if (LeaderBoardFile.is_open()){
		for (const auto& var : highscores) {
			LeaderBoardFile << PLAYER_NAME_TEXT << var.name << "\n";
			LeaderBoardFile << PLAYER_SCORE_TEXT << var.score << "\n";
		}
	}
}

void LeaderBoard::reset() {
	WriteToFile(HS_FILE_NAME);
	highscores.clear();
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
	DrawTextSV(NEW_HS_TEXT, X_RENDER_INDENT, Y_RENDER_INDENT, FONT_SIZE_LARGE, YELLOW);
	DrawTextSV(ENTER_NAME_TEXT, X_RENDER_INDENT, Y_RENDER_INDENT * 2, FONT_SIZE_SMALL, YELLOW);
	DrawRectangleRec(NAME_TEXTBOX, LIGHTGRAY);
	DrawRectangleLinesEx(NAME_TEXTBOX, LINE_THICKNESS, RED);
	DrawTextF(name.data(), NAME_TEXTBOX.x + NAME_OFFSET_X, NAME_TEXTBOX.y + NAME_OFFSET_Y, FONT_SIZE_MEDIUM, MAROON);
	DrawText(TextFormat(INPUT_TEXT.data(), letterCount, MAX_LETTER_COUNT - 1), X_RENDER_INDENT, Y_RENDER_INDENT * 3, FONT_SIZE_SMALL, YELLOW);

	if (letterCount > 0 && letterCount < MAX_LETTER_COUNT){
		DrawTextSV(CONFIRM_TEXT, X_RENDER_INDENT, Y_RENDER_INDENT * 4, FONT_SIZE_MEDIUM, YELLOW);
	}
}

void LeaderBoard::HSRender() const noexcept{
	DrawTextSV(CONTINUE_TEXT, X_RENDER_INDENT, Y_RENDER_INDENT, FONT_SIZE_MEDIUM, YELLOW);
	DrawTextSV(LEADERBOARD_TEXT, LEADERBOARD_X_OFFSET, LEADERBOARD_Y_OFFSET - FONT_SIZE_MEDIUM, FONT_SIZE_MEDIUM, YELLOW);

	int i = 0;
	for (const auto& var : highscores) {
		DrawText(var.name.data(), LEADERBOARD_X_OFFSET, LEADERBOARD_Y_OFFSET + (i * FONT_SIZE_MEDIUM), FONT_SIZE_MEDIUM, YELLOW);
		DrawText(TextFormat("%i", var.score), LEADERBOARD_SCORE_X_OFFSEET, LEADERBOARD_Y_OFFSET + (i * FONT_SIZE_MEDIUM), FONT_SIZE_MEDIUM, YELLOW);
		i++;
	}
}

