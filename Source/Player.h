#pragma once
#include "pch.h"
#include "EntityType.h"
#include "Direction.h"

constexpr float PLAYER_SPEED = 7.f;
constexpr float PLAYER_POSITION_Y = 1010.f;
constexpr float PLAYER_RADIUS = 50.f;
constexpr float PLAYER_SIZE = PLAYER_RADIUS * 2.f;
constexpr float PLAYER_SPRITE_SIZE = 352.f;
constexpr float PLAYER_ANIMATION_TIMER = 0.4f;
constexpr int	PLAYER_MAX_HEALTH = 3;

struct Player
{
	Player() noexcept;

	Rectangle rec = { 0, PLAYER_POSITION_Y, PLAYER_SIZE, PLAYER_SIZE };
	//float x_pos = 0; 
	Direction direction = Direction::STATIC;
	int lives = PLAYER_MAX_HEALTH;
	float textureTimer = 0;
	int activeTexture = 0;

	EntityType type = EntityType::PLAYER;

	void Render(Texture2D texture) const noexcept;
	void Update() noexcept;
	void Movement() noexcept;
	void Collision() noexcept;
	void Animation() noexcept; //TODO: make into an object
	void reset() noexcept; //TODO: mayeb be unsused
	Vector2 getPosition() const noexcept;
	float getPositionX() const noexcept;
};