#pragma once
#include "game.h"
#include "Window.h"
#include "Drawing.h"
#include "LeaderBoard.h"
#include "StartScreen.h"
#include "GameStates.h"

constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;
constexpr int FPS = 60;
constexpr std::string_view TITLE = "Space Invaders";

class Application {
    GameState currentState = GameState::STARTSCREEN;
    Window window{ WINDOW_WIDTH, WINDOW_HEIGHT, TITLE, FPS };

    StartScreen startScreen;
    Game game;
    LeaderBoard leaderboard;

    int score = 0;
    void doStartScreen() noexcept;
    void doGameplay();
    void doLeaderBoard();
public:
	void run();
};