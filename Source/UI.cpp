#include "pch.h"
#include "UI.h"

void UI::Render(int score, int lives) const noexcept {
	DrawText(TextFormat(SCORE_TEXT.data(), score), TEXT_POS_X, SCORE_TEXT_POS_Y, FONT_SIZE, YELLOW);
	DrawText(TextFormat(LIVES_TEXT.data(), lives), TEXT_POS_X, LIVES_TEXT_POS_Y, FONT_SIZE, YELLOW);
}
