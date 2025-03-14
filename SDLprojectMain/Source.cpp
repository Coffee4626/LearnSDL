#include "EventHandle.h"

using namespace std;

Game* game = NULL;

int main(int argc, char* argv[])
{
    game = new Game();

    game->gameLoop();

    return 0;
}


