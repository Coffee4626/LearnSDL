#include "EventHandle.h"


enum Buttons
{
	LEFT_PADDLE_UP,
	LEFT_PADDLE_DOWN,
	RIGHT_PADDLE_UP,
	RIGHT_PADDLE_DOWN,
	TOTAL_PADDLE = 4,
};

bool ButtonsInput[TOTAL_PADDLE];

Game::Game()
{
	gWindow = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, "Game");
	gRenderer = createRenderer(gWindow);
	paddle1 = Paddle(50, SCREEN_HEIGHT / 2);
	paddle2 = Paddle(SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2);
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
			if (event.type == SDL_KEYDOWN)
			{
				std::cout << "Key pressed" << std::endl;
				switch (event.key.keysym.sym)
				{
					case SDLK_w:
						ButtonsInput[LEFT_PADDLE_UP] = true;
						break;
					case SDLK_s:
						ButtonsInput[LEFT_PADDLE_DOWN] = true;
						break;
					case SDLK_UP:
						ButtonsInput[RIGHT_PADDLE_UP] = true;
						break;
					case SDLK_DOWN:
						ButtonsInput[RIGHT_PADDLE_DOWN] = true;
						break;
				}
			}

			if (event.type == SDL_KEYUP)
			{
				std::cout << "Key not pressed" << std::endl;
				switch (event.key.keysym.sym)
				{
					case SDLK_w:
						ButtonsInput[LEFT_PADDLE_UP] = false;
						break;
					case SDLK_s:
						ButtonsInput[LEFT_PADDLE_DOWN] = false;
						break;
					case SDLK_UP:
						ButtonsInput[RIGHT_PADDLE_UP] = false;
						break;
					case SDLK_DOWN:
						ButtonsInput[RIGHT_PADDLE_DOWN] = false;
						break;
				}
			}
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		std::cout << "Not doing anything" << std::endl;

		if (ButtonsInput[LEFT_PADDLE_UP] == false)
		{
			paddle1.paddleDirectionY = 0;
		}

		if (ButtonsInput[LEFT_PADDLE_DOWN] == false)
		{
			paddle1.paddleDirectionY = 0;
		}

		if (ButtonsInput[RIGHT_PADDLE_UP] == false)
		{
			paddle2.paddleDirectionY = 0;
		}

		if (ButtonsInput[RIGHT_PADDLE_DOWN] == false)
		{
			paddle2.paddleDirectionY = 0;
		}

		if (ButtonsInput[LEFT_PADDLE_UP] == true)
		{
			paddle1.paddleDirectionY = -1;
		}

		if (ButtonsInput[LEFT_PADDLE_DOWN] == true)
		{
			paddle1.paddleDirectionY = 1;
		}

		if (ButtonsInput[RIGHT_PADDLE_UP] == true)
		{
			paddle2.paddleDirectionY = -1;
		}

		if (ButtonsInput[RIGHT_PADDLE_DOWN] == true)
		{
			paddle2.paddleDirectionY = 1;
		}

		paddle1.UpdatePaddlePosition(deltaTime);
		paddle2.UpdatePaddlePosition(deltaTime);

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