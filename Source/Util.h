#pragma once
#include "pch.h"
#include <string_view>

float GetScreenWidthF() noexcept;
float GetScreenHeightF() noexcept;

float GetRandomValueF(int min, int max) noexcept;

void DrawTextF(const char* text, float x, float y, unsigned fontSize, Color color) noexcept;
void DrawTextSV(std::string_view text, int x, int y, unsigned fontSize, Color color) noexcept;
