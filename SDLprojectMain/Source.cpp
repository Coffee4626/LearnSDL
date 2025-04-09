#include "Game.h"

using namespace pong;

Game* game;

int main(int argc, char* argv[])
{
    game = new Game();

    game->GameLoop();

    return 0;
}


