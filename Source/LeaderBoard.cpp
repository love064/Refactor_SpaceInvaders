#include "LeaderBoard.h"

#include <iostream> //TODO: check which are in use
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>

#define DISABLE_WARNINGS_FROM_RAYLIB \
    __pragma(warning(push)) \
    /* C26812: The enum type '...' is unscoped. Prefer 'enum class' over 'enum' (Enum.3) */ \
    __pragma(warning(disable : 26812)) \
    /* C26446: Prefer to use gsl::at() instead of unchecked subscript operator (bounds.4). */ \
    __pragma(warning(disable : 26446)) \
    /* C26455: Default constructor is not declared as noexcept */ \
    __pragma(warning(disable : 26455)) \
    /* C26426: Global initializer calls a non-constexpr function */ \
    __pragma(warning(disable : 26426)) \
    /* C26409: Avoid calling new and delete explicitly, use smart pointers */ \
    __pragma(warning(disable : 26409)) \
    /* C26477: Use 'override' instead of base class member name */ \
    __pragma(warning(disable : 26477)) \
    /* C26433: Function can be marked as noexcept */ \
    __pragma(warning(disable : 26433)) \
    /* C26818: Prefer std::vector over C array */ \
    __pragma(warning(disable : 26818)) \
    /* C26440: Function can be declared 'const' */ \
    __pragma(warning(disable : 26440))


GameState LeaderBoard::update(int score) {
	if (newHighScore) {
		yourScore.score = score;
		SetName();
	}
	if (IsKeyReleased(KEY_SPACE) && !newHighScore) {
		//reset();
		return GameState::STARTSCREEN;
	}
	return GameState::ENDSCREEN;
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
	if (LeaderBoardFile.is_open()) { //TODO: revert if statement if(!open) break;
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

void LeaderBoard::SortLeaderBoard() { //TODO: looking into this, may swap?
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

void LeaderBoard::render() const noexcept {
	if (newHighScore) {
		SetNameRender();
	}
	else {
		HSRender();
	}
}

void LeaderBoard::SetNameRender() const noexcept{ //TODO: refactor away c style casting
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

#define RESTORE_WARNINGS __pragma(warning(pop))