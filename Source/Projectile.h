#pragma once
#include "pch.h"
#include "EntityType.h"
#include "Direction.h"

constexpr float PROJECTILE_SPEED = 15;
constexpr float PROJECTILE_SIZE_X = 1;
constexpr float PROJECTILE_SIZE_Y = 50;

struct Projectile{
	Rectangle rec = { 0, 0, PROJECTILE_SIZE_X, PROJECTILE_SIZE_Y };
	EntityType type = EntityType::PLAYER_PROJECTILE;
	bool active = true;
	Direction direction = Direction::UP;

	Projectile(EntityType type, Vector2 pos) noexcept;
	
	void Update() noexcept;
	void Collision() noexcept;
	void Render(Texture2D texture) const noexcept;
};