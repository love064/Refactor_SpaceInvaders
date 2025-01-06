#pragma once
#include "pch.h"
#include "EntityType.h"
#include "Direction.h"

constexpr float PLAYER_SPEED = 7.f;
constexpr float PLAYER_POSITION_Y = 70.f;
constexpr float PLAYER_RADIUS = 50.f;
constexpr float PLAYER_SPRITE_SIZE = 352.f;
constexpr float PLAYER_ANIMATION_TIMER = 0.4f;
constexpr int	PLAYER_MAX_HEALTH = 3;

struct Player
{
	Player() noexcept;

	float x_pos = 0; 
	Direction direction = Direction::STATIC;
	int lives = PLAYER_MAX_HEALTH;
	float textureTimer = 0;
	int activeTexture = 0;

	EntityType type = EntityType::PLAYER;

	void Render(Texture2D texture) const noexcept;
	void Update() noexcept;
	void Movement() noexcept;
	void Animation() noexcept;
	void reset() noexcept; //TODO: mayeb be unsused
};