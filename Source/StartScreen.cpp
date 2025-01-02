#include "StartScreen.h"
#include "raylib.h"

void StartScreen::render() const noexcept {
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);

	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
}
