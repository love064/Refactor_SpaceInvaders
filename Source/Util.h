#pragma once
#include "raylib.h"

float getLineLength(Vector2 A, Vector2 B) noexcept; //TODO: go over these three functions and refactor
bool isPointInCircle(Vector2 circlePos, float radius, Vector2 point) noexcept;
bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd) noexcept;
float GetScreenWidthF() noexcept;
float GetScreenHeightF() noexcept;