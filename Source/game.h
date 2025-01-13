#pragma once
#include <vector>
#include "Textures.h"
#include "Player.h"
#include "Projectile.h"
#include "Wall.h"
#include "Alien.h"
#include "Stars.h"
#include "GameStates.h"
#include "Animation.h"
#include "UI.h"

constexpr int WALL_COUNT = 5;
constexpr float WALL_MARGIN_X = 0.75F;
constexpr float WALL_Y_OFFSET = 250;
constexpr int STAR_COUNT = 600;
constexpr int FORMATION_ROW = 8;
constexpr int FORMATION_COLLUM = 5;
constexpr float ALIEN_SPACING = 100;
constexpr float FORMATION_X = 100;
constexpr float FORMATION_Y = 50;

struct Game {
	int score = 0; 
	float shootTimer = 0;
	bool newHighScore = false;

	Textures alienTexture{ "./Assets/Alien.png" };
	Textures barrierTexture{ "./Assets/Barrier.png" };
	Textures laserTexture{ "./Assets/Laser.png" };

	Textures shipTexture1{ "./Assets/Ship1.png" }; //TODO: should game or player own animation?
	Textures shipTexture2{ "./Assets/Ship2.png" };
	Textures shipTexture3{ "./Assets/Ship3.png" };
	Animation playerAnimation{ {shipTexture1.get(), shipTexture2.get(), shipTexture3.get()} };
	
	Game() noexcept(false);
	void End() noexcept;
	void reset();

	GameState Update();
	void PlayerShooting();
	void AlienShooting();
	void Render() const;
	void checkCollisions(auto& projectile, auto& entities) const noexcept;
	void Collisions() noexcept;

	void SpawnAliens();

	UI ui;
	Player player;
	std::vector<Projectile> enemyProjectiles;
	std::vector<Projectile> playerProjectiles;
	std::vector<Wall> walls;
	std::vector<Alien> aliens;
	Background background{ STAR_COUNT };
};