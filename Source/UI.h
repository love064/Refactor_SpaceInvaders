#pragma once
#include <string_view>

constexpr std::string_view SCORE_TEXT = "Score: %i";
constexpr std::string_view LIVES_TEXT = "Lives: %i";
constexpr int FONT_SIZE = 40;
constexpr int TEXT_POS_X = 50;
constexpr int SCORE_TEXT_POS_Y = 20;
constexpr int LIVES_TEXT_POS_Y = 70;

struct UI {
	void Render(int score, int lives) const noexcept;
};