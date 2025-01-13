#pragma once

#include <string_view>
#include <vector>
#include <string>
#include "pch.h"
#include "GameStates.h"

constexpr int MAX_LETTER_COUNT = 9;
constexpr int X_RENDER_INDENT = 600;
constexpr int Y_RENDER_INDENT = 200;
constexpr int FONT_SIZE_SMALL = 20;
constexpr int FONT_SIZE_MEDIUM = 40;
constexpr int FONT_SIZE_LARGE = 60;
constexpr int LINE_THICKNESS = 2;
constexpr int NAME_OFFSET_X = 5;
constexpr int NAME_OFFSET_Y = 8;
constexpr int LEADERBOARD_X_OFFSET = 50;
constexpr int LEADERBOARD_Y_OFFSET = 140;
constexpr int LEADERBOARD_SCORE_X_OFFSEET = 350;
constexpr Rectangle NAME_TEXTBOX = { 600, 500, 225, 50 };
constexpr std::string_view NEW_HS_TEXT = "NEW HIGHSCORE!";
constexpr std::string_view ENTER_NAME_TEXT = "ENTER NAME!";
constexpr std::string_view INPUT_TEXT = "INPUT CHARS: %i/%i";
constexpr std::string_view CONFIRM_TEXT = "PRESS ENTER TO CONTINUE";
constexpr std::string_view CONTINUE_TEXT = "PRESS SPACE TO CONTINUE";
constexpr std::string_view LEADERBOARD_TEXT = "LEADERBOARD";
constexpr std::string_view HS_FILE_NAME = "Assets/LeaderBoard.txt";
constexpr std::string_view PLAYER_NAME_TEXT = "Player Name:";
constexpr std::string_view PLAYER_SCORE_TEXT = "Score:";
constexpr unsigned LEADERBOARD_COUNT = 5;

struct PlayerData {
	std::string name;
	int score = 0;
};

struct LeaderBoard {
	std::vector<PlayerData> highscores;

	bool newHighScore = true;
	PlayerData yourScore = {"", 0};
	std::string name;
	int letterCount = 0;
	
	GameState update(int score);
	void SetName();

	void ReadFromFile(std::string_view fileName);
	void ReadPlayerData(std::ifstream& LeaderBoardFile);
	void SortLeaderBoard();
	void WriteToFile(std::string_view fileName) const;

	void reset();

	void SetNameRender() const noexcept;
	void HSRender() const noexcept;
	void render() const noexcept;
};