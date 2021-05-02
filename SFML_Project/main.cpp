#include "Game.h"

int main() 
{
    Game game;

    while (game.IsRunning())
    {
        game.Update();
        game.Draw();
    }

    return EXIT_SUCCESS;
}