#pragma once
#include "raylib.h"
#include <vector>
#include <string>
#include "Textures.h"
#include "Player.h"
#include "Projectile.h"
#include "Wall.h"
#include "Alien.h"
#include "Stars.h"
#include "LeaderBoard.h"

//TODO: split into different files (player.h, etc.)

enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

//struct PlayerData
//{
//	std::string name;
//	int score;
//};

constexpr int WALL_COUNT = 5;
constexpr int FORMATION_ROW = 8;
constexpr int FORMATION_COLLUM = 5;
constexpr int ALIEN_SPACING = 80;
constexpr int FORMATION_X = 100;
constexpr int FORMATION_Y = 50;


struct Game //TODO: remove unneccecary comments
{
	int score = 0; //TODO: uninit
	float shootTimer = 0;
	bool newHighScore = false;
	bool isCurrentState = false;

	Textures alienTexture{ "./Assets/Alien.png" };
	Textures barrierTexture{ "./Assets/Barrier.png" };
	Textures laserTexture{ "./Assets/Laser.png" };
	Textures shipTexture1{ "./Assets/Ship1.png" };
	Textures shipTexture2{ "./Assets/Ship2.png" };
	Textures shipTexture3{ "./Assets/Ship3.png" };

	std::vector<Texture2D> playerTextures{shipTexture1.get(), shipTexture2.get(), shipTexture3.get()};
	
	Game() noexcept;
	void End() noexcept;
	void reset() noexcept;

	void Update();
	void Render();

	void SpawnAliens();

	Player player;
	std::vector<Projectile> Projectiles;
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens;
	Background background;

	Vector2 playerPos;
	Vector2 alienPos; 
	Vector2 cornerPos;
	float offset;
};