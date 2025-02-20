#include "EventHandle.h"



Game::Game()
{
	gWindow = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, "Game");
	gRenderer = createRenderer(gWindow);
	paddle1 = Paddle(300, 300);
	paddle2 = Paddle(200, 300);
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
			paddle1.PaddleMovement1(event, deltaTime);
			paddle2.PaddleMovement2(event, deltaTime);

			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		render();
	}
	quitSDL(gWindow, gRenderer);
}

void Game::render()
{
	SDL_RenderClear(gRenderer);


	paddle1.drawPaddle(gRenderer);

	paddle2.drawPaddle(gRenderer);

	/*SDL_RenderCopy(gRenderer, gTexturePaddle, NULL, NULL);*/

	SDL_RenderPresent(gRenderer);
}