#pragma once
#include "game.h"
#include "Window.h"
#include "Drawing.h"
#include "LeaderBoard.h"
#include "StartScreen.h"
#include "GameStates.h"

struct Application {
    GameState currentState = GameState::STARTSCREEN;
    Window window{ 1920, 1080, "Space Invaders", 60 };

    StartScreen startScreen;
    Game game;
    LeaderBoard leaderboard;

    int score = 0;

	void run();
    void doStartScreen() noexcept;
    void doGameplay();
    void doLeaderBoard();

};