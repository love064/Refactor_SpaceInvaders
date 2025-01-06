#pragma once
#include "pch.h"
#include "EntityType.h"
#include "Direction.h"

constexpr float PROJECTILE_SPEED = 15;
constexpr float PROJECTILE_SPRITE_SIZE = 176;
constexpr float PROJECTILE_SIZE = 50;
constexpr float PROJECTILE_HITBOX_OFFSET = 15;

struct Projectile{
	Vector2 position = { 0,0 };
	EntityType type = EntityType::PLAYER_PROJECTILE;
	bool active = true;
	Direction direction = Direction::UP;

	Projectile(EntityType type, Vector2 pos) noexcept;
	
	void Update() noexcept;
	void Render(Texture2D texture) const noexcept;

	Vector2 getLineStart() const noexcept;
	Vector2 getLineEnd() const noexcept;
};