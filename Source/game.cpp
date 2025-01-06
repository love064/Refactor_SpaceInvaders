#include "game.h"
#include <iostream> //TODO: SEE WHICH ones can go
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include "Util.h"

Game::Game() noexcept{
	reset();
}

void Game::End() noexcept{
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();
	//player.reset();
	isCurrentState = false;
}

void Game::reset() noexcept {
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


void Game::Update() //TODO: move to the left, and make shorter/break apart, noexcpt
{
	if (IsKeyReleased(KEY_Q))
	{
		End();
	}

	//Update Player
	player.Update();
		
	//Update Aliens and Check if they are past player
	for (auto& alien : Aliens) {
		alien.Update();

		if (alien.getPositionY() > GetScreenHeightF() - PLAYER_POSITION_Y) {
			End();
		}
	}

	//End game if player dies
	if (player.lives < 1){
		End();
	}

	//Spawn new aliens if aliens run out
	if (Aliens.empty()){
		SpawnAliens();
	}

	// Update background with offset
	playerPos = { player.x_pos, PLAYER_POSITION_Y };
	cornerPos = { 0, PLAYER_POSITION_Y };
	offset = getLineLength(playerPos, cornerPos) * -1;
	background.Update(offset / 15);


	//UPDATE PROJECTILE
	for (auto& projectile : Projectiles) {
		projectile.Update();
	}
	for (auto& wall : Walls) {
		wall.Update();
	}

	//CHECK ALL COLLISONS HERE
	for (int i = 0; i < Projectiles.size(); i++)
	{
		if (Projectiles[i].type == EntityType::PLAYER_PROJECTILE)
		{
			for (int a = 0; a < Aliens.size(); a++)
			{
				if (CheckCollision(Aliens[a].position, ALIEN_RADIUS, Projectiles[i].getLineStart(), Projectiles[i].getLineEnd()))
				{
					// Kill!
					std::cout << "Hit! \n";
					// Set them as inactive, will be killed later
					Projectiles[i].active = false;
					Aliens[a].active = false;
					score += 100;
				}
			}
		}

		//ENEMY PROJECTILES HERE
		for (int i = 0; i < Projectiles.size(); i++)
		{
			if (Projectiles[i].type == EntityType::ENEMY_PROJECTILE)
			{
				if (CheckCollision({player.x_pos, GetScreenHeight() - PLAYER_POSITION_Y }, PLAYER_RADIUS, Projectiles[i].getLineStart(), Projectiles[i].getLineEnd()))
				{
					std::cout << "dead!\n"; 
					Projectiles[i].active = false; 
					player.lives -= 1; 
				}
			}
		}


		for (int b = 0; b < Walls.size(); b++)
		{
			if (CheckCollision(Walls[b].position, Walls[b].radius, Projectiles[i].getLineStart(), Projectiles[i].getLineEnd()))
			{
				// Kill!
				std::cout << "Hit! \n";
				// Set them as inactive, will be killed later
				Projectiles[i].active = false;
				Walls[b].health -= 1;
			}
		}
	}

	//MAKE PROJECTILE
	if (IsKeyPressed(KEY_SPACE)) {
		Vector2 spawnPoint = { player.x_pos, GetScreenHeightF() - PLAYER_RADIUS * 2 + 30 };
		Projectiles.emplace_back(EntityType::PLAYER_PROJECTILE, spawnPoint);
	}

	//Aliens Shooting
	shootTimer += 1;
	if (shootTimer > 59) //once per second
	{
		int randomAlienIndex = 0;

		if (Aliens.size() > 1)
		{
			randomAlienIndex = rand() % Aliens.size();
		}

		Projectiles.emplace_back(EntityType::ENEMY_PROJECTILE, Aliens[randomAlienIndex].position);
		shootTimer = 0;
	}

	//storge killing pruning etc
	//TODO: erase-remove is an old idiom. prefer erase_if
	Aliens.erase(std::remove_if(Aliens.begin(), Aliens.end(), [](const Alien& a) { return !a.active; }), Aliens.end());
	Walls.erase(std::remove_if(Walls.begin(), Walls.end(), [](const Wall& w) { return !w.active; }), Walls.end());
	Projectiles.erase(std::remove_if(Projectiles.begin(), Projectiles.end(), [](const Projectile& p) { return !p.active; }), Projectiles.end());
}


void Game::Render() //TODO: move to the left, and make shorter
{
	//background render LEAVE THIS AT TOP
	background.Render();

	//DrawText("GAMEPLAY", 50, 30, 40, YELLOW);
	DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
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
void Game::SpawnAliens() noexcept{
	for (int row = 0; row < FORMATION_COLLUM; row++) {
		for (int col = 0; col < FORMATION_ROW; col++) {
			Vector2 spawnPoint = { FORMATION_X + ALIEN_X_SPAWN_OFFSET + (col * ALIEN_SPACING), FORMATION_Y + (row * ALIEN_SPACING) };
			Aliens.emplace_back(spawnPoint);
		}
	}
}