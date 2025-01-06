#pragma once
#include "pch.h"
#include <vector>
#include "Textures.h"
#include "Player.h"
#include "Projectile.h"
#include "Wall.h"
#include "Alien.h"
#include "Stars.h"

constexpr int WALL_COUNT = 5;
constexpr int STAR_COUNT = 600;
constexpr int FORMATION_ROW = 8;
constexpr int FORMATION_COLLUM = 5;
constexpr float ALIEN_SPACING = 100;
constexpr float FORMATION_X = 100;
constexpr float FORMATION_Y = 50;


struct Game //TODO: go through render
{
	int score = 0; 
	float shootTimer = 0;
	bool newHighScore = false;
	bool isCurrentState = false;

	Textures alienTexture{ "./Assets/Alien.png" };
	Textures barrierTexture{ "./Assets/Barrier.png" };
	Textures laserTexture{ "./Assets/Laser.png" };
	Textures shipTexture1{ "./Assets/Ship1.png" }; //TODO: consider creating an Animation to handle this
	Textures shipTexture2{ "./Assets/Ship2.png" };
	Textures shipTexture3{ "./Assets/Ship3.png" };

	std::vector<Texture2D> playerTextures{shipTexture1.get(), shipTexture2.get(), shipTexture3.get()};
	
	Game();
	void End() noexcept;
	void reset();

	void Update();
	void Inputs();
	void AlienShooting();
	void Render() const noexcept;
	void Collisions() noexcept;

	void SpawnAliens();

	Player player;
	std::vector<Projectile> Projectiles;
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens;
	Background background{ STAR_COUNT };
};