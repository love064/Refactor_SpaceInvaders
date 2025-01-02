#include "LeaderBoard.h"

#include <iostream> //TODO: check which are in use
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>


void LeaderBoard::update(int score) {
	if (newHighScore) {
		yourScore.score = score;
		SetName();
	}
}

void LeaderBoard::SetName() {
	int key = GetCharPressed();
	while (key > 0) {
		if ((key >= 32) && (key <= 125) && (letterCount < 9)) {
			name += static_cast<char>(key);
			letterCount++;
		}
		key = GetCharPressed();
	}

	if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0) {
		name.pop_back();
		letterCount--;
	}

	if (letterCount > 0 && letterCount < 9 && IsKeyReleased(KEY_ENTER)) {
		yourScore.name = name;
		ReadFromFile("Assets/LeaderBoard.txt");
		SortLeaderBoard();
		newHighScore = false;
	}
}

void LeaderBoard::ReadFromFile(std::string_view fileName) {
	std::ifstream LeaderBoardFile(fileName.data(), std::ios::out | std::ios::binary);
	if (LeaderBoardFile.is_open()) {
		for (int i = 0; i < 5; i++) {
			std::string line;
			PlayerData currentPlayer;

			while (std::getline(LeaderBoardFile, line)) {
				if (line.find("Player Name:") != std::string::npos) {
					currentPlayer.name = line.substr(13);
				}
				else if (line.find("Score:") != std::string::npos) {
					std::istringstream(line.substr(7)) >> currentPlayer.score;
					Leaderboard.push_back(currentPlayer);  
				}
			}
		}
			LeaderBoardFile.close();
	}
}

void LeaderBoard::SortLeaderBoard() {
	for (int i = 0; i < Leaderboard.size(); i++){
		if (yourScore.score > Leaderboard[i].score){
			Leaderboard.insert(Leaderboard.begin() + i, yourScore);
			Leaderboard.pop_back();
			break;
		}
	}
}

void LeaderBoard::WriteToFile(std::string_view fileName) const {
	std::ofstream LeaderBoardFile(fileName.data(), std::ios::out | std::ios::binary);
	if (LeaderBoardFile.is_open()){
		for (const auto& var : Leaderboard) {
			LeaderBoardFile << "Player Name: " << var.name << "\n";
			LeaderBoardFile << "Score: " << var.score << "\n";
		}
		LeaderBoardFile.close();
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

void LeaderBoard::render() noexcept {
	if (newHighScore) {
		SetNameRender();
	}
	else {
		HSRender();
	}
}

void LeaderBoard::SetNameRender() const noexcept{
	DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);

	// BELOW CODE IS FOR NAME INPUT RENDER
	DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

	DrawRectangleRec(textBox, LIGHTGRAY);
	DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);

	//Draw the name being typed out
	DrawText(name.data(), (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

	//Draw the text explaining how many characters are used
	DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

		//if (letterCount < 9)
		//{
		//	// Draw blinking underscore char
		//	if (((framesCounter / 20) % 2) == 0)
		//	{
		//		DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
		//	}

		//}
		//else
		//{
		//	//Name needs to be shorter
		//	DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
		//}

	// Explain how to continue when name is input
	if (letterCount > 0 && letterCount < 9)
	{
		DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
	}
}

void LeaderBoard::HSRender() const noexcept{
	// If no highscore or name is entered, show scoreboard and call it a day
	DrawText("PRESS SPACE TO CONTINUE", 600, 200, 40, YELLOW);

	DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

	int i = 0;
	for (const auto& var : Leaderboard) {
		DrawText(var.name.data(), 50, 140 + (i * 40), 40, YELLOW);
		DrawText(TextFormat("%i", var.score), 350, 140 + (i * 40), 40, YELLOW);
		i++;
	}
}