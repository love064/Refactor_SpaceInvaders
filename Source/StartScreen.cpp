#include "StartScreen.h"
#include "pch.h"

GameState StartScreen::update() const noexcept {
    if (IsKeyReleased(KEY_SPACE)) {
        return GameState::GAMEPLAY;
    }
    return GameState::STARTSCREEN;
}

void StartScreen::render() const noexcept {
	DrawText("SPACE INVADERS", START_SCREEN_INDENT_X, TITLE_INDENT_Y, FONT_SIZE_TITLE, YELLOW);
	DrawText("PRESS SPACE TO BEGIN", START_SCREEN_INDENT_X, START_INDENT_Y, FONT_SIZE_MED, YELLOW);
}
