#include "UI.h"
#include "pch.h"

void UI::Render(int score, int lives) const noexcept {
	DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW); //TODO: magci values (string)
	DrawText(TextFormat("Lives: %i", lives), 50, 70, 40, YELLOW);
}
