#include "LeaderBoard.h"

#include <iostream> //TODO: check which are in use
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>


bool CheckNewHighScore(int score, const std::vector<PlayerData>& Leaderboard) noexcept
{
	if (score > Leaderboard[4].score)
	{
		return true;
	}

	return false;
}

std::vector<PlayerData> InsertNewHighScore(std::string_view name, int score, const std::vector<PlayerData>& Leaderboard)
{
	PlayerData newData;
	newData.name = name;
	newData.score = score;

	std::vector<PlayerData> tempboard = Leaderboard;

	for (int i = 0; i < tempboard.size(); i++)
	{
		if (newData.score > tempboard[i].score)
		{

			tempboard.insert(tempboard.begin() + i, newData);

			tempboard.pop_back();

			i = tempboard.size();

		}
	}
	return tempboard;
}
//

void LeaderBoard::update(int score) {
	if (newHighScore) {
		yourScore.score = score;
		SetName();
	}

	if (IsKeyReleased(KEY_ENTER) && !newHighScore)
	{
		//Continue(); reset
	}

}

void LeaderBoard::SetName() {
	int key = GetCharPressed();
	while (key > 0) {
		if ((key >= 32) && (key <= 125) && (letterCount < 9)) {
			name[letterCount] = static_cast<char>(key);
			name[letterCount + 1] = '\0';
			letterCount++;
		}
		key = GetCharPressed();
	}

	if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0) {
		name[letterCount - 1] = '\0';
		letterCount--;
	}

	if (letterCount > 0 && letterCount < 9 && IsKeyReleased(KEY_ENTER)) {
		for (int i = 0; i < 4; ++i) {
			yourScore.name = name;
		}

		ReadFromFile(".\LeaderBoard.txt"); //TODO: check if this is the right address
		SortLeaderBoard();
		newHighScore = false;
	}
}

void LeaderBoard::ReadFromFile(std::string_view fileName) {
	std::ifstream LeaderBoardFile(fileName.data(), std::ios::out | std::ios::binary);
	if (LeaderBoardFile.is_open()) {
		for (int i = 0; i < 5; i++) {
			Leaderboard.emplace_back( "ABC", 0 );
			LeaderBoardFile.read((char*)&Leaderboard[i], sizeof(PlayerData));
		}
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
			const size_t nameLength = var.name.size();
			LeaderBoardFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
			LeaderBoardFile.write(var.name.data(), nameLength);
			LeaderBoardFile.write(reinterpret_cast<const char*>(&var.score), sizeof(var.score));
		}
	}
}

void LeaderBoard::render() {
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
	DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

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

void LeaderBoard::HSRender() noexcept{
	// If no highscore or name is entered, show scoreboard and call it a day
	DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);

	DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

	for (int i = 0; i < Leaderboard.size(); i++)
	{
		const auto tempNameDisplay = Leaderboard[i].name;
		DrawText(tempNameDisplay.data(), 50, 140 + (i * 40), 40, YELLOW);
		DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * 40), 40, YELLOW);
	}
}