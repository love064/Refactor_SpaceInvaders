#include "Application.h"

void Application::run() {
    Drawing drawing(BLACK);

    switch (currentState) {
        using enum GameState;
    case STARTSCREEN:
        doStartScreen();
        break;

    case GAMEPLAY:
        doGameplay();
        break;

    case ENDSCREEN:
        doLeaderBoard();
        break;
    }
}

void Application::doStartScreen() noexcept {
    currentState = startScreen.update();
    startScreen.render();
}

void Application::doGameplay() {
    currentState = game.Update();
    game.Render();
    if (currentState == GameState::ENDSCREEN) {
        score = game.score;
        game.reset();
    }
}

void Application::doLeaderBoard() {
    currentState = leaderboard.update(score);
    leaderboard.render();
    if (currentState == GameState::STARTSCREEN) {
        leaderboard.reset();
    }
}