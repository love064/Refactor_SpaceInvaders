#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include "Util.h"
#include "LeaderBoard.h"

void Game::Start() //TODO: double init 
{
	// creating walls 
	const auto window_width = static_cast<float>(GetScreenWidth()); 
	const auto window_height = static_cast<float>(GetScreenHeight());
	const auto wall_distance = window_width / (wallCount + 1.f); 
	for (int i = 0; i < wallCount; i++)
	{
		Wall newWalls;
		newWalls.position.y = window_height - 250; 
		newWalls.position.x = wall_distance * (i + 1); 

		Walls.push_back(newWalls); 

	}


	//creating player
	const Player newPlayer;
	player = newPlayer;
	player.Initialize();

	//creating aliens
	SpawnAliens();
	

	//creating background
	Background newBackground;
	newBackground.Initialize(600);
	background = newBackground;

	//reset score
	score = 0;

	gameState = State::GAMEPLAY;

}

void Game::End()
{
	//SAVE SCORE AND UPDATE SCOREBOARD
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();
	newHighScore = CheckNewHighScore(score, Leaderboard);
	gameState = State::ENDSCREEN;
}

void Game::Continue() noexcept
{
	//SaveLeaderboard();
	gameState = State::STARTSCREEN;
}


void Game::Update() //TODO: move to the left, and make shorter/break apart
{
	switch (gameState)
	{
	case State::STARTSCREEN:
		//Code 
		if (IsKeyReleased(KEY_SPACE))
		{
			Start();


		}

		break;
	case State::GAMEPLAY:
		//Code
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

			if (Aliens[i].position.y > GetScreenHeight() - player.player_base_height)
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
		playerPos = { player.x_pos, static_cast<float>(player.player_base_height) };
		cornerPos = { 0, static_cast<float>(player.player_base_height) };
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
					if (CheckCollision(Aliens[a].position, Aliens[a].radius, Projectiles[i].lineStart, Projectiles[i].lineEnd))
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
					if (CheckCollision({player.x_pos, GetScreenHeight() - player.player_base_height }, player.radius, Projectiles[i].lineStart, Projectiles[i].lineEnd))
					{
						std::cout << "dead!\n"; 
						Projectiles[i].active = false; 
						player.lives -= 1; 
					}
				}
			}


			for (int b = 0; b < Walls.size(); b++)
			{
				if (CheckCollision(Walls[b].position, Walls[b].radius, Projectiles[i].lineStart, Projectiles[i].lineEnd))
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
		if (IsKeyPressed(KEY_SPACE))
		{
			float window_height = static_cast<float>(GetScreenHeight());
			Projectile newProjectile;
			newProjectile.position.x = player.x_pos;
			newProjectile.position.y = window_height - 130;
			newProjectile.type = EntityType::PLAYER_PROJECTILE;
			Projectiles.push_back(newProjectile);
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

			Projectile newProjectile;
			newProjectile.position = Aliens[randomAlienIndex].position;
			newProjectile.position.y += 40;
			newProjectile.speed = -15;
			newProjectile.type = EntityType::ENEMY_PROJECTILE;
			Projectiles.push_back(newProjectile);
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

			
		

	break;
	case State::ENDSCREEN:
		//Code
	
		//Exit endscreen
		if (IsKeyReleased(KEY_ENTER) && !newHighScore)
		{
			Continue();
		}

	

		if (newHighScore)
		{
			int key = GetCharPressed();

				// Check if more characters have been pressed on the same frame
				while (key > 0)
				{
					// NOTE: Only allow keys in range [32..125]
					if ((key >= 32) && (key <= 125) && (letterCount < 9))
					{
						name[letterCount] = static_cast<char>(key);
						name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
						letterCount++;
					}

					key = GetCharPressed();  // Check next character in the queue
				}

				//Remove chars 
				if (IsKeyPressed(KEY_BACKSPACE))
				{
					letterCount--;
					if (letterCount < 0) letterCount = 0;
					name[letterCount] = '\0';
				}

			// If the name is right legth and enter is pressed, exit screen by setting highscore to false and add 
			// name + score to scoreboard
			if (letterCount > 0 && letterCount < 9 && IsKeyReleased(KEY_ENTER))
			{
				const std::string_view nameEntry = name; //TODO: BROKEN ONLY ONE NAME AT A TIME (replaces the old one)

				Leaderboard = InsertNewHighScore(nameEntry, score, Leaderboard);

				newHighScore = false;
			}


		}
		


		break;
	default:
		//SHOULD NOT HAPPEN
		break;
	}
}


void Game::Render() //TODO: move to the left, and make shorter
{
	switch (gameState)
	{
	case State::STARTSCREEN:
		//Code
		DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);

		DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);


		break;
	case State::GAMEPLAY:
		//Code


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






		break;
	case State::ENDSCREEN:
		//Code
		//DrawText("END", 50, 50, 40, YELLOW);


		

		


		if (newHighScore)
		{
			DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);



			// BELOW CODE IS FOR NAME INPUT RENDER
			DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

			DrawRectangleRec(textBox, LIGHTGRAY);
			if (mouseOnText)
			{
				// HOVER CONFIRMIATION
				DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
			}
			else
			{
				DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
			}

			//Draw the name being typed out
			DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

			//Draw the text explaining how many characters are used
			DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

			if (mouseOnText)
			{
				if (letterCount < 9)
				{
					// Draw blinking underscore char
					if (((framesCounter / 20) % 2) == 0)
					{
						DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
					}

				}
				else
				{
					//Name needs to be shorter
					DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
				}
				
			}

			// Explain how to continue when name is input
			if (letterCount > 0 && letterCount < 9)
			{
				DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
			}

		}
		else {
			// If no highscore or name is entered, show scoreboard and call it a day
			DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);

			DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

			for (int i = 0; i < Leaderboard.size(); i++)
			{
				const auto tempNameDisplay = Leaderboard[i].name;
				DrawText(tempNameDisplay.data(), 50, 140 + (i * 40), 40, YELLOW);
				DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * 40), 40, YELLOW);
			}
		}

		


		break;
	default:
		//SHOULD NOT HAPPEN
		break;
	}
}

void Game::SpawnAliens()
{
	for (int row = 0; row < formationHeight; row++) {
		for (int col = 0; col < formationWidth; col++) {
			Alien newAlien = Alien();
			newAlien.active = true;
			newAlien.position.x = formationX + 450 + (col * alienSpacing);
			newAlien.position.y = formationY + (row * alienSpacing);
			Aliens.push_back(newAlien);
			std::cout << "Find Alien -X:" << newAlien.position.x << std::endl;
			std::cout << "Find Alien -Y:" << newAlien.position.y << std::endl;
		}
	}

}
//
//bool Game::CheckNewHighScore()
//{
//	if (score > Leaderboard[4].score)
//	{
//		return true;
//	}
//
//	return false;
//}
//
//void Game::InsertNewHighScore(std::string name)
//{
//	PlayerData newData;
//	newData.name = name;
//	newData.score = score;
//
//	for (int i = 0; i < Leaderboard.size(); i++)
//	{
//		if (newData.score > Leaderboard[i].score)
//		{
//
//			Leaderboard.insert(Leaderboard.begin() + i, newData);
//
//			Leaderboard.pop_back();
//
//			i = Leaderboard.size();
//
//		}
//	}
//}
//
//void Game::LoadLeaderboard()
//{
//	// CLEAR LEADERBOARD
//
//	// OPEN FILE
//
//	// READ DATA
//
//	// WRITE DATA ONTO LEADERBOARD
//
//	//CLOSE FILE
//}
//
//void Game::SaveLeaderboard()
//{
//	// SAVE LEADERBOARD AS ARRAY
//
//	// OPEN FILE
//	std::fstream file;
//
//	file.open("Leaderboard");
//
//	if (!file)
//	{
//		std::cout << "file not found \n";
//
//	}
//	else
//	{
//		std::cout << "file found \n";
//	}
//	// CLEAR FILE
//
//	// WRITE ARRAY DATA INTO FILE
//
//	// CLOSE FILE
//}
