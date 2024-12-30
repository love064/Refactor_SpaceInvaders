#pragma once
#include "raylib.h"
#include "EntityType.h"

struct Alien
{
public:

	Color color = WHITE; //TODO: doesnt change (unused?)
	Vector2 position = { 0, 0 }; //TODO: magic numbers
	int x = 0;
	int y = 0;
	float radius = 30;
	bool active = true;
	bool moveRight = true;

	EntityType type = EntityType::ENEMY;

	int speed = 2;

	void Update();
	void Render(Texture2D texture);
};