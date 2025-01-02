#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include "Util.h"
//#include "LeaderBoard.h"

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
		Wall newWalls; //TODO: double init
		newWalls.position.y = GetScreenHeightF() - 250;
		newWalls.position.x = wall_distance * (i + 1);

		Walls.push_back(newWalls);
	}

	const Player newPlayer;
	player = newPlayer;

	//creating aliens
	SpawnAliens();

	//creating background
	Background newBackground;
	newBackground.Initialize(600);
	background = newBackground;

	//reset score
	score = 0;
}


void Game::Update() //TODO: move to the left, and make shorter/break apart
{
	if (IsKeyReleased(KEY_Q))
	{
		End();
	}

	//Update Player
	player.Update();
		
	//Update Aliens and Check if they are past player
	for (int i = 0; i < Aliens.size(); i++)
	{
		Aliens[i].Update(); 

		if (Aliens[i].position.y > GetScreenHeight() - PLAYER_POSITION_Y)
		{
			End();
		}
	}

	//End game if player dies
	if (player.lives < 1)
	{
		End();
	}

	//Spawn new aliens if aliens run out
	if (Aliens.size() < 1)
	{
		SpawnAliens();
	}


	// Update background with offset
	playerPos = { player.x_pos, PLAYER_POSITION_Y };
	cornerPos = { 0, PLAYER_POSITION_Y };
	offset = lineLength(playerPos, cornerPos) * -1;
	background.Update(offset / 15);


	//UPDATE PROJECTILE
	for (int i = 0; i < Projectiles.size(); i++)
	{
		Projectiles[i].Update();
	}
	//UPDATE PROJECTILE
	for (int i = 0; i < Walls.size(); i++)
	{
		Walls[i].Update();
	}

	//CHECK ALL COLLISONS HERE
	for (int i = 0; i < Projectiles.size(); i++)
	{
		if (Projectiles[i].type == EntityType::PLAYER_PROJECTILE)
		{
			for (int a = 0; a < Aliens.size(); a++)
			{
				if (CheckCollision(Aliens[a].position, Aliens[a].radius, Projectiles[i].getLineStart(), Projectiles[i].getLineEnd()))
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

	// REMOVE INACTIVE/DEAD ENITITIES
	for (int i = 0; i < Projectiles.size(); i++)
	{
		if (Projectiles[i].active == false)
		{
			Projectiles.erase(Projectiles.begin() + i);
			// Prevent the loop from skipping an instance because of index changes, since all insances after
			// the killed objects are moved down in index. This is the same for all loops with similar function
			i--;
		}
	}
	for (int i = 0; i < Aliens.size(); i++)
	{
		if (Aliens[i].active == false)
		{
			Aliens.erase(Aliens.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < Walls.size(); i++)
	{
		if (Walls[i].active == false)
		{
			Walls.erase(Walls.begin() + i);
			i--;
		}
	}
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

void Game::SpawnAliens()
{
	for (int row = 0; row < FORMATION_COLLUM; row++) {
		for (int col = 0; col < FORMATION_ROW; col++) {
			Alien newAlien = Alien();
			newAlien.active = true; //TODO: Double INIT
			newAlien.position.x = FORMATION_X + 450 + (col * ALIEN_SPACING);
			newAlien.position.y = FORMATION_Y + (row * ALIEN_SPACING);
			Aliens.push_back(newAlien);
			std::cout << "Find Alien -X:" << newAlien.position.x << std::endl;
			std::cout << "Find Alien -Y:" << newAlien.position.y << std::endl;
		}
	}

}