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
	// Gamestate
	State gameState = {};

	// Score
	int score; //TODO: uninit

	// for later, make a file where you can adjust the number of walls (config file) 
	

	//Aliens shooting
	float shootTimer = 0;

	bool newHighScore = false;

	Textures alienTexture{ "./Assets/Alien.png" };
	Textures barrierTexture{ "./Assets/Barrier.png" };
	Textures laserTexture{ "./Assets/Laser.png" };
	Textures shipTexture1{ "./Assets/Ship1.png" };
	Textures shipTexture2{ "./Assets/Ship2.png" };
	Textures shipTexture3{ "./Assets/Ship3.png" };

	std::vector<Texture2D> playerTextures{shipTexture1.get(), shipTexture2.get(), shipTexture3.get()};
	
	Game() noexcept;

	void Start(); //TODO: Double init
	void End() noexcept;		//TODO: this start and contiune should be incorporated in a reset/end and reset function

	void Continue() noexcept; //TODO: Double init

	bool isCurrentState = false;
	void reset();

	void Update();
	void Render();

	void SpawnAliens();


	/*bool CheckNewHighScore();
	void InsertNewHighScore(std::string name);

	void LoadLeaderboard();
	void SaveLeaderboard();*/


	// Entity Storage and Resources
	//Resources resources;

	Player player;

	std::vector<Projectile> Projectiles;

	std::vector<Wall> Walls;

	std::vector<Alien> Aliens;

	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };
	
	Background background;



	Vector2 playerPos;
	Vector2 alienPos; 
	Vector2 cornerPos;
	float offset;



	//TEXTBOX ENTER
	char name[9 + 1] = "\0";      //One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;

};