#pragma once
#include "pch.h"
#include "EntityType.h"

constexpr int WALL_MAX_HEALTH = 50;
constexpr int WALL_SIZE_X = 200;
constexpr int WALL_SIZE_Y = 90;
constexpr int WALL_TEXT_SIZE = 40;
constexpr int WALL_TEXT_OFFSET_X = ( WALL_SIZE_X / 2 ) - (WALL_TEXT_SIZE / 2);
constexpr int WALL_TEXT_OFFSET_Y = WALL_SIZE_Y / 2;

struct Wall{
	Rectangle rec = { 0, 0, WALL_SIZE_X, WALL_SIZE_Y };
	bool active = true;
	int health = WALL_MAX_HEALTH;

	explicit Wall(Vector2 pos) noexcept;

	void Update() noexcept;
	void Collision() noexcept;
	void Render(Texture2D texture) const noexcept;

	int getPosXI() const noexcept;
	int getPosYI() const noexcept;
};