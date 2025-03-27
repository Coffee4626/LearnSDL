#include "SceneManager.h"

using namespace std;

SceneManager* game;

int main(int argc, char* argv[])
{
    game = new SceneManager();

    game->MainLoop();

    return 0;
}


