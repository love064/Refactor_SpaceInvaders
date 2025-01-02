#include "raylib.h"
#include "game.h"
#include "Window.h"
#include "Drawing.h"
#include "LeaderBoard.h"

enum struct GameState {
    STARTSCREEN,
    GAMEPLAY,
    ENDSCREEN
};



int main(void)
{   
    Window window( 1920, 1080 ); //TODO: ERROR handling for both window, drawing and resources
    

    GameState currentState = GameState::GAMEPLAY;

    Game game = { State::STARTSCREEN };
    LeaderBoard leaderboard;

    int score = 0;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Drawing drawing;
        
        switch (currentState){
        case GameState::STARTSCREEN:
            if (IsKeyReleased(KEY_SPACE)){
                currentState = GameState::GAMEPLAY;
            }

            break;
        case GameState::GAMEPLAY:
            game.Update();
            game.Render();
            break;
        case GameState::ENDSCREEN:
            leaderboard.update(score);
            leaderboard.render();
            break;
        }
    }

    return 0;
}