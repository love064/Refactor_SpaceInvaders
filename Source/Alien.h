#pragma once
#include "raylib.h"
#include "EntityType.h"

constexpr int ALIEN_SIZE = 100;
constexpr int ALIEN_SPRITE_SIZE = 352;
constexpr int ALIEN_SPRITE_ORIGN = 50;
constexpr float ALIEN_RADIUS = 30.f;
constexpr float ALIEN_SPEED = 2.f;
constexpr int ALIEN_Y_DROP_AMOUNT = 50;
constexpr int ALIEN_X_SPAWN_OFFSET = 450;

struct Alien{
	Vector2 position = { 0, 0 }; 
	float radius = ALIEN_RADIUS;
	bool active = true;
	bool moveRight = true;
	float speed = ALIEN_SPEED;
	EntityType type = EntityType::ENEMY;

	explicit Alien(Vector2 pos) noexcept;

	void Update() noexcept;
	void Render(Texture2D texture) const noexcept;
};