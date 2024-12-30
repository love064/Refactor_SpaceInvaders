#include "raylib.h"
#include "game.h"
#include "Window.h"
#include "Drawing.h"

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

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Drawing drawing;
        
        switch (currentState){
        case GameState::STARTSCREEN:
            //
            break;
        case GameState::GAMEPLAY:
            game.Update();
            game.Render();
            break;
        case GameState::ENDSCREEN:
            //
            break;
        }
    }

    return 0;
}