#pragma once
#include "pch.h"

constexpr float PLAYER_SPEED = 7.f;
constexpr float PLAYER_POSITION_Y = 950.f;
constexpr float PLAYER_SIZE = 100;
constexpr float PLAYER_RADIUS = PLAYER_SIZE/2;
constexpr float PLAYER_ANIMATION_TIMER = 0.4f;
constexpr int	PLAYER_MAX_HEALTH = 3;

struct Player{
	Vector2 pos = { 0, PLAYER_POSITION_Y };
	int lives = PLAYER_MAX_HEALTH;
	float vel = 0;
	
	Player() noexcept;

	void Render(Texture2D texture) const noexcept;
	void Update() noexcept;
	void Collision() noexcept;
	Rectangle getRec() const noexcept;
	float getPositionX() const noexcept;
};