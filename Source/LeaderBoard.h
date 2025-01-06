#pragma once

#include <string_view>
#include <vector>
#include "pch.h"
#include <string>

struct PlayerData
{
	std::string name;
	int score = 0;
};

class LeaderBoard {
	std::vector<PlayerData> Leaderboard;// = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };
public: //TODO: check which can be private

	bool newHighScore = true;
	PlayerData yourScore = {"", 0};
	//char name[9 + 1] = "\0";
	std::string name;
	int letterCount = 0;
	Rectangle textBox = { 600, 500, 225, 50 };

	
	void update(int score);
	void SetName();

	void ReadFromFile(std::string_view fileName);
	void SortLeaderBoard();
	void WriteToFile(std::string_view fileName) const;

	void reset();

	void SetNameRender() const noexcept;
	void HSRender() const noexcept;
	void render() const noexcept;
};
//
//bool CheckNewHighScore(int score, const std::vector<PlayerData>& Leaderboard) noexcept;
//std::vector<PlayerData> InsertNewHighScore(std::string_view name, int score, const std::vector<PlayerData>& Leaderboard);
//void LoadLeaderboard();
//void SaveLeaderboard();