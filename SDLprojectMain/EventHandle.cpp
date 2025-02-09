#include "EventHandle.h"
#include "loadMedia.h"
Game::Game()
{
	gWindow = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, "test");
	gRenderer = createRenderer(gWindow);
	paddle1 = Paddle(100, 100);
}

void Game::gameLoop()
{
	bool quit = false;
	float deltaTime = (SDL_GetTicks() - tickcounts) / 1000.0f;
	tickcounts = SDL_GetTicks();
	while (!quit)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			paddle1.paddleMovement(event, deltaTime);
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		SDL_RenderClear(gRenderer);

		paddle1.drawPaddle(gRenderer);

		SDL_RenderPresent(gRenderer);
	}
	quitSDL(gWindow, gRenderer);
}

void Game::render()
{

}