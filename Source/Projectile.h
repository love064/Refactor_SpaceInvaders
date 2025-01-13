#pragma once
#include "pch.h"
#include "EntityType.h"
#include "Direction.h"

constexpr float PROJECTILE_SPEED = 15;
constexpr float PROJECTILE_SIZE_X = 1;
constexpr float PROJECTILE_SIZE_Y = 50;

struct Projectile{
	Vector2 pos = { 0, 0 };
	float vel = 0;

	bool active = true;
	
	Projectile(Vector2 position, float velocity) noexcept;
	
	void Update() noexcept;
	void Collision() noexcept;
	void Render(Texture2D texture) const noexcept;
	Rectangle getRec() const noexcept;
};