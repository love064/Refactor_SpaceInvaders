#pragma once
#include "pch.h"
#include "EntityType.h"

constexpr int WALL_MAX_HEALTH = 50;
constexpr int WALL_RADIUS = 60;
constexpr float WALL_SPRITE_SIZE = 704;
constexpr float WALL_SPRITE_ORIGN = 100;
constexpr float WALL_SIZE = 200;
constexpr int WALL_TEXT_OFFSET_X = 21;
constexpr int WALL_TEXT_OFFSET_Y = 10;
constexpr int WALL_TEXT_SIZE = 40;

struct Wall{
	//Vector2 position = {0, 0};
	Rectangle rec = { 0, 0, WALL_SIZE, WALL_SIZE };
	bool active = true;
	int health = WALL_MAX_HEALTH;
	int radius = WALL_RADIUS;

	explicit Wall(Vector2 pos) noexcept;

	void Update() noexcept;
	void Collision() noexcept;
	void Render(Texture2D texture) const noexcept;

	int getPosXI() const noexcept;
	int getPosYI() const noexcept;
};