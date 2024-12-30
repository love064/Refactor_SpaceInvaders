#include "raylib.h"
#include "game.h"
#include "RayLibWindow.h"

int main(void)
{   
    //const int screenWidth = 1920; //TODO: RAII window init
    //const int screenHeight = 1080; //TODO: RAII window init

    Window window( 1920, 1080 );

    //InitWindow(screenWidth, screenHeight, "SPACE INVADERS"); //TODO: RAII for the window

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Game game = { State::STARTSCREEN };
    Resources resources; //TODO: RAII 
    game.resources = resources;
    game.Launch();

    
    //--------------------------------------------------------------------------------------

    InitAudioDevice();

    auto sound = LoadSound("./hitHurt.ogg"); //TODO: RAII, may not be used?
    



    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        //if (IsKeyPressed(KEY_SPACE))
        //{
        //    PlaySound(sound);
        //}

        //if (IsKeyPressed(KEY_BACKSPACE))
        //{
        //    StopSound(sound);
        //}

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
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    //CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    std::string filename = "level.txt";  

    return 0;
}