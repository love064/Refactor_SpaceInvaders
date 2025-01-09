#pragma once
#include "pch.h"
#include "EntityType.h"
#include "Direction.h"

constexpr float PLAYER_SPEED = 7.f;
constexpr float PLAYER_POSITION_Y = 950.f;
constexpr float PLAYER_SIZE = 100;
constexpr float PLAYER_RADIUS = PLAYER_SIZE/2;
constexpr float PLAYER_ANIMATION_TIMER = 0.4f;
constexpr int	PLAYER_MAX_HEALTH = 3;

struct Player
{
	Player() noexcept;

	Rectangle rec = { 0, PLAYER_POSITION_Y, PLAYER_SIZE, PLAYER_SIZE };
	Direction direction = Direction::STATIC;
	int lives = PLAYER_MAX_HEALTH;
	EntityType type = EntityType::PLAYER;

	void Render(Texture2D texture) const noexcept;
	void Update() noexcept;
	void Movement() noexcept;
	void Collision() noexcept;
	Vector2 getPosition() const noexcept;
	float getPositionX() const noexcept;
};