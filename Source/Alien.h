#pragma once

#include "pch.h"
#include "EntityType.h"

constexpr int ALIEN_SIZE = 100;
constexpr float ALIEN_SPEED = 2.f;
constexpr int ALIEN_Y_DROP_AMOUNT = 50;

struct Alien{
	Rectangle rec = { 0, 0, ALIEN_SIZE, ALIEN_SIZE };
	bool active = true;
	bool moveRight = true;
	float speed = ALIEN_SPEED;
	EntityType type = EntityType::ENEMY;

	explicit Alien(Vector2 pos) noexcept;

	void Update() noexcept;
	void Render(Texture2D texture) const noexcept;
	void Collision() noexcept;

	Vector2 getPosition() const noexcept;
	float getPositionX() const noexcept;
	float getPositionY() const noexcept;
};