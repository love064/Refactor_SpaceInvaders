#pragma once
#include "GameStates.h"
#include <string_view>

constexpr int FONT_SIZE_TITLE = 160;
constexpr int FONT_SIZE_MED = 40;
constexpr int START_SCREEN_INDENT_X = 200;
constexpr int TITLE_INDENT_Y = 100;
constexpr int START_INDENT_Y = 350;
constexpr std::string_view TITLE_TEXT = "SPACE INVADERS";
constexpr std::string_view BEGIN_TEXT = "PRESS SPACE TO BEGIN";

struct StartScreen {
	GameState update() const noexcept;
	void render() const noexcept;
};