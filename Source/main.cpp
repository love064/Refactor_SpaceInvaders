#include "raylib.h"
#include "game.h"
#include "RayLibWindow.h"

int main(void)
{   
    Window window( 1920, 1080 ); //TODO: ERROR handling for both window and resources
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Game game = { State::STARTSCREEN };
    game.Launch(); //TODO: Double init

    
    //--------------------------------------------------------------------------------------

    InitAudioDevice();

    auto sound = LoadSound("./hitHurt.ogg"); //TODO: RAII, may not be used?
    



    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        game.Update();
      

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing(); //TODO: RAII Drawing

        ClearBackground(BLACK);

       

        game.Render();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseAudioDevice();

    std::string filename = "level.txt";  //TODO: ??? maybe unused

    return 0;
}