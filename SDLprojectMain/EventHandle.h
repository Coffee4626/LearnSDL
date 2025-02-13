#ifndef EVENT_HANDLE
#define EVENT_HANDLE

#include "gameBase.h"
#include "Paddle.h"

class Game
{
public:
	Game();
	~Game() = default;

	void gameLoop();
	void render();

private:
	Uint32 tickcounts;
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	Paddle paddle1;
	Paddle paddle2;
};

#endif // !EVENT_HANDLE
