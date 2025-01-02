#pragma once
#include "raylib.h"
#include <vector>

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
	std::vector<Star> Stars;

	explicit Background(int starAmount) noexcept;

	void Update(float offset) noexcept;
	void Render() const noexcept;
};