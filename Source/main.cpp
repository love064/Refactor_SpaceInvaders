#include "raylib.h"
#include "game.h"
#include "Window.h"
#include "Drawing.h"

int main(void)
{   
    Window window( 1920, 1080 ); //TODO: ERROR handling for both window, drawing and resources

    Game game = { State::STARTSCREEN };
    game.Launch(); //TODO: Double init

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        game.Update();
      

        Drawing drawing;
        game.Render();
    }
    //std::string filename = "level.txt";  //TODO: ??? maybe unused

    return 0;
}