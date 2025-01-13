#include "Util.h"

float GetScreenWidthF() noexcept {
	return static_cast<float>(GetScreenWidth());
}

float GetScreenHeightF() noexcept {
	return static_cast<float>(GetScreenHeight());
}

float GetRandomValueF(int min, int max) noexcept {
	return static_cast<float>(GetRandomValue(min, max));
}

void DrawTextF(const char* text, float x, float y, unsigned fontSize, Color color) noexcept {
	DrawText(text, static_cast<int>(x), static_cast<int>(y), fontSize, color);
}

void DrawTextSV(std::string_view text, int x, int y, unsigned fontSize, Color color) noexcept {
	DrawText(text.data(), x, y, fontSize, color);
}

