#include "pch.h"
#include "Game.h"
#include "Constants.h"

int main(int argc, char* argv[]) {
    Game game;

    game.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, FRAME_TARGET_TIME);

    while (game.IsRunning())
    {
        game.ProcessInput();
        game.Update();
        game.Render();
    }

    game.Destroy();

    return 0;
}
