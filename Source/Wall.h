#pragma once
#include "raylib.h"
#include "EntityType.h"

struct Wall
{
public:
	Vector2 position; //TODO: uninitialised
	Rectangle rec;
	bool active;
	Color color;
	int health = 50; //TODO: magic numbers
	int radius = 60;


	void Render(Texture2D texture);
	void Update();
};