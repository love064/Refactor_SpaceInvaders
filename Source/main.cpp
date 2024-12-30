#include "raylib.h"
#include "game.h"
#include "RayLibWindow.h"
#include "Drawing.h"

int main(void)
{   
    Window window( 1920, 1080 ); //TODO: ERROR handling for both window and resources
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Game game = { State::STARTSCREEN };
    game.Launch(); //TODO: Double init

    //InitAudioDevice()
   // auto sound = LoadSound("./hitHurt.ogg"); //TODO: RAII, may not be used?
    
   
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        game.Update();
      

        Drawing drawing;
        game.Render();
    }

    //CloseAudioDevice();

    std::string filename = "level.txt";  //TODO: ??? maybe unused

    return 0;
}