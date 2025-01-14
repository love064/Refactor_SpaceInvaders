#include "StartScreen.h"
#include "pch.h"
#include "Util.h"

GameState StartScreen::update() const noexcept {
    if (IsKeyReleased(KEY_SPACE)) {
        return GameState::GAMEPLAY;
    }
    return GameState::STARTSCREEN;
}

void StartScreen::render() const noexcept {
	DrawTextSV(TITLE_TEXT, START_SCREEN_INDENT_X, TITLE_INDENT_Y, FONT_SIZE_TITLE, YELLOW);
	DrawTextSV(BEGIN_TEXT, START_SCREEN_INDENT_X, START_INDENT_Y, FONT_SIZE_MED, YELLOW);
}
