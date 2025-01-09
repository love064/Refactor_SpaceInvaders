#pragma once

#include <string_view>
#include <vector>
#include <string>
#include "pch.h"
#include "GameStates.h"

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
	Rectangle textBox = { 600, 500, 225, 50 };
	
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