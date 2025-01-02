#pragma once
#include "raylib.h"
#include "EntityType.h"

constexpr int WALL_MAX_HEALTH = 50;
constexpr int WALL_RADIUS = 60;
constexpr float WALL_SPRITE_SIZE = 704;
constexpr float WALL_SIZE = 200;
constexpr int WALL_TEXT_OFFSET_X = 21;
constexpr int WALL_TEXT_OFFSET_Y = 10;
constexpr int WALL_TEXT_SIZE = 40;

struct Wall{
	Vector2 position = {0, 0};
	bool active = true;
	int health = WALL_MAX_HEALTH;
	int radius = WALL_RADIUS;

	explicit Wall(Vector2 pos) noexcept;

	void Render(Texture2D texture) const noexcept;
	void Update() noexcept;

	int getPosXI() const noexcept;
	int getPosYI() const noexcept;
};