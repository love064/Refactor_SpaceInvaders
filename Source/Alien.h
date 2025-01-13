#pragma once
#include "pch.h"
#include "EntityType.h"

constexpr int ALIEN_SIZE = 100;
constexpr float ALIEN_SPEED = 2.f;
constexpr int ALIEN_Y_DROP_AMOUNT = 50;

struct Alien{
	Vector2 pos = { 0,0 };
	float vel = 1;
	bool active = true;

	explicit Alien(Vector2 position) noexcept;

	void Update() noexcept;
	void Render(Texture2D texture) const noexcept;
	void Collision() noexcept;

	float getPositionY() const noexcept;
	Rectangle getRec() const noexcept;
};