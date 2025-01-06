#include "game.h"
#include <iostream> //TODO: SEE WHICH ones can go
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>

#include "Util.h"

#define DISABLE_WARNINGS_FROM_RAYLIB \
    __pragma(warning(push)) \
    /* C26812: The enum type '...' is unscoped. Prefer 'enum class' over 'enum' (Enum.3) */ \
    __pragma(warning(disable : 26812)) \
    /* C26446: Prefer to use gsl::at() instead of unchecked subscript operator (bounds.4). */ \
    __pragma(warning(disable : 26446)) \
    /* C26455: Default constructor is not declared as noexcept */ \
    __pragma(warning(disable : 26455)) \
    /* C26426: Global initializer calls a non-constexpr function */ \
    __pragma(warning(disable : 26426)) \
    /* C26409: Avoid calling new and delete explicitly, use smart pointers */ \
    __pragma(warning(disable : 26409)) \
    /* C26477: Use 'override' instead of base class member name */ \
    __pragma(warning(disable : 26477)) \
    /* C26433: Function can be marked as noexcept */ \
    __pragma(warning(disable : 26433)) \
    /* C26818: Prefer std::vector over C array */ \
    __pragma(warning(disable : 26818)) \
    /* C26440: Function can be declared 'const' */ \
    __pragma(warning(disable : 26440))

Game::Game(){
	reset();
}

void Game::End() noexcept{ //TODO: check if deallocation is noexcept
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();
	//player.reset(); //TODO: not used
	isCurrentState = false;
}

void Game::reset(){
	const auto wall_distance = GetScreenWidthF() / (WALL_COUNT + 1.f); //TODO: maybe delete (only used once)
	for (int i = 0; i < WALL_COUNT; i++) {
		const Vector2 spawnPoint = { wall_distance * (i + 1), GetScreenHeightF() - 250};
		Walls.emplace_back(spawnPoint);
	}	
	player = {};	
	SpawnAliens();		
	background = Background(STAR_COUNT);
	score = 0;
}


void Game::Update(){
	player.Update();
	if (player.lives < 1){
		End();
	}
	
	for (auto& alien : Aliens) {
		alien.Update();
		if (alien.getPositionY() > PLAYER_POSITION_Y) {
			End();
		}
	}
	if (Aliens.empty()){
		SpawnAliens();
	}

	for (auto& projectile : Projectiles) {
		projectile.Update();
	}
	for (auto& wall : Walls) {
		wall.Update();
	}

	const float offset = ((GetScreenWidthF() / 2.f) - player.getPositionX()) / 10.f; //TODO: MAGIC number
	background.Update(offset);

	Inputs();
	AlienShooting();
	Collisions();

	//TODO: [](const Alien& a) { return !a.active; } could be a namespace
	std::erase_if(Aliens, [](const Alien& a) { return !a.active; });
	std::erase_if(Walls, [](const Wall& w) { return !w.active; });
	std::erase_if(Projectiles, [](const Projectile& p) { return !p.active; });
}

void Game::Inputs(){
	if (IsKeyReleased(KEY_Q)) {
		End();
	}

	if (IsKeyPressed(KEY_SPACE)) {
		Vector2 spawnPoint = { player.getPositionX(), PLAYER_POSITION_Y};
		Projectiles.emplace_back(EntityType::PLAYER_PROJECTILE, spawnPoint);
	}
}

void Game::AlienShooting() {
	shootTimer += 1;
	if (shootTimer >= 60){
		if (Aliens.empty()) {
			return;
		}
		const int randomNumber = GetRandomValue(0, Aliens.size() - 1); 

		Projectiles.emplace_back(EntityType::ENEMY_PROJECTILE, Aliens[randomNumber].getPosition());
		shootTimer = 0;
	}
}

void Game::Collisions() noexcept {
	for (auto& projectile : Projectiles) {
		for (auto& wall : Walls) {
			if (CheckCollisionRecs(projectile.rec, wall.rec)) {
				projectile.Collision();
				wall.Collision();
			}
		}

		if (projectile.type == EntityType::ENEMY_PROJECTILE && CheckCollisionRecs(projectile.rec, player.rec)) {
			projectile.Collision();
			player.Collision();
		}

		for (auto& alien : Aliens) {
			if (projectile.type == EntityType::PLAYER_PROJECTILE && CheckCollisionRecs(projectile.rec, alien.rec)) {
				projectile.Collision();
				alien.Collision();
				score += 100;
			}
		}
	}
}

void Game::Render() //TODO: move to the left, and make shorter
{
	//background render LEAVE THIS AT TOP
	background.Render();

	//DrawText("GAMEPLAY", 50, 30, 40, YELLOW);
	DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW); //TODO: make UI object
	DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);

	//player rendering 
	player.Render(playerTextures[player.activeTexture]);

	//projectile rendering
	for (int i = 0; i < Projectiles.size(); i++)
	{
		Projectiles[i].Render(laserTexture.get());
	}

	// wall rendering 
	for (int i = 0; i < Walls.size(); i++)
	{
		Walls[i].Render(barrierTexture.get()); 
	}

	//alien rendering  
	for (int i = 0; i < Aliens.size(); i++)
	{
		Aliens[i].Render(alienTexture.get());
	}
}

//TODO: you claim noexcept but you are allocating memory. allocation can always throw. 
//either catch and swallow or declare noexcept false.
void Game::SpawnAliens(){
	for (int row = 0; row < FORMATION_COLLUM; row++) {
		for (int col = 0; col < FORMATION_ROW; col++) {
			Vector2 spawnPoint = { FORMATION_X + ALIEN_X_SPAWN_OFFSET + (col * ALIEN_SPACING), FORMATION_Y + (row * ALIEN_SPACING) };
			Aliens.emplace_back(spawnPoint);
		}
	}
}

#define RESTORE_WARNINGS __pragma(warning(pop))