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

struct PlayerData {
	std::string name;
	int score = 0;
};

struct LeaderBoard {
	std::vector<PlayerData> Leaderboard;

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
	int getTextboxXI() const noexcept;
	int getTextboxYI() const noexcept;
};