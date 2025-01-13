#pragma once
#include "pch.h"
#include <vector>

constexpr int PLAYER_TO_STAR_OFFSET_DIVIDER = 10;
constexpr int STAR_MAX_SIZE = 4;
constexpr int STAR_MIN_SIZE = 1;
constexpr int STAR_X_OFFSET = 150;

struct Star{
	float initX = 0;
	Vector2 position = { 0, 0 };
	float size = 0;

	Star() noexcept;

	void Update(float starOffset) noexcept;
	void Render() const noexcept;

	int getPositionX() const noexcept;
	int getPositionY() const noexcept;
};

struct Background{
	std::vector<Star> stars;

	explicit Background(unsigned starAmount);

	void Update(float playerPositionX) noexcept;
	void Render() const noexcept;
};