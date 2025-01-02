#include "raylib.h"
#include "game.h"
#include "Window.h"
#include "Drawing.h"
#include "LeaderBoard.h"
#include "StartScreen.h"

enum struct GameState {
    STARTSCREEN,
    GAMEPLAY,
    ENDSCREEN
};


int main(void)
{   
    Window window( 1920, 1080 ); //TODO: ERROR handling for both window, drawing and resources
    
    GameState currentState = GameState::STARTSCREEN;

    StartScreen startScreen;
    Game game;
    LeaderBoard leaderboard;

    int score = 0;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Drawing drawing;
        
        switch (currentState){
        case GameState::STARTSCREEN:
            if (IsKeyReleased(KEY_SPACE)){
                game.isCurrentState = true;
                currentState = GameState::GAMEPLAY;
            }
            startScreen.render();
            break;

        case GameState::GAMEPLAY:
            game.Update();
            game.Render();
            if (!game.isCurrentState) {
                currentState = GameState::ENDSCREEN;
                score = game.score;
                game.reset();
            }
            break;

        case GameState::ENDSCREEN:
            leaderboard.update(score);
            leaderboard.render();
            if (IsKeyReleased(KEY_SPACE) && !leaderboard.newHighScore)
            {
                leaderboard.reset();
                currentState = GameState::STARTSCREEN;
            }
            break;
        }
    }

    return 0;
}