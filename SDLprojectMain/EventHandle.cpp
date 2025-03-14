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

void Game::InitObject()
{
	paddle1 = new Paddle(50, SCREEN_HEIGHT / 2);
	paddle2 = new Paddle(SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2);
	ball = new Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	deltaTime = (SDL_GetTicks() - tickcounts) / 1000.0f;
	tickcounts = SDL_GetTicks();
	player1score.LoadFromRenderedText(std::to_string(p1score), scoreFont, { 0xFF, 0xFF, 0xFF, 0xFF }, gRenderer);
	player2score.LoadFromRenderedText(std::to_string(p2score), scoreFont, { 0xFF, 0xFF, 0xFF, 0xFF }, gRenderer);
}

void Game::InitGame()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) 
	{
		std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return;
	}

	if (TTF_Init() == -1) 
	{
		std::cout << "Unable to initialize TTF: " << TTF_GetError() << std::endl;
		return;
	}

	gWindow = SDL_CreateWindow("PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		std::cout << "Unable to create SDL window: " << SDL_GetError() << std::endl;
		return;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL) 
	{
		std::cout << "Unable to create SDL renderer: " << SDL_GetError() << std::endl;
		return;
	}

	scoreFont = TTF_OpenFont("Assets/DejaVuSansMono.ttf", 40);
	if (scoreFont == NULL) 
	{
		std::cout << "Unable to load a font for the application: " << TTF_GetError() << std::endl;
	}
}

Game::Game()
{
	scoreFont = NULL;
	gWindow = NULL;
	gRenderer = NULL;
	paddle1 = NULL;
	paddle2 = NULL;
	ball = NULL;
}

void Game::GetInput()
{
	if (event.type == SDL_KEYDOWN)
	{
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
}

void Game::HandleInput()
{
	if (ButtonsInput[LEFT_PADDLE_UP] == false)
	{
		paddle1->paddleDirectionY = 0;
	}

	if (ButtonsInput[LEFT_PADDLE_DOWN] == false)
	{
		paddle1->paddleDirectionY = 0;
	}

	if (ButtonsInput[RIGHT_PADDLE_UP] == false)
	{
		paddle2->paddleDirectionY = 0;
	}

	if (ButtonsInput[RIGHT_PADDLE_DOWN] == false)
	{
		paddle2->paddleDirectionY = 0;
	}

	if (ButtonsInput[LEFT_PADDLE_UP] == true)
	{
		paddle1->paddleDirectionY = -1;
	}

	if (ButtonsInput[LEFT_PADDLE_DOWN] == true)
	{
		paddle1->paddleDirectionY = 1;
	}

	if (ButtonsInput[RIGHT_PADDLE_UP] == true)
	{
		paddle2->paddleDirectionY = -1;
	}

	if (ButtonsInput[RIGHT_PADDLE_DOWN] == true)
	{
		paddle2->paddleDirectionY = 1;
	}
}

void Game::close()
{
	//Free loaded texture
	player1score.Free();
	player2score.Free();
	scoreTexture.Free();

	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	TTF_CloseFont(scoreFont);
	scoreFont = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}


void Game::UpdateObjects()
{
	paddle1->UpdatePaddlePosition(deltaTime);
	paddle2->UpdatePaddlePosition(deltaTime);
	ball->UpdateBallPosition(deltaTime);
	//update score
}


void Game::render()
{
	SDL_RenderClear(gRenderer);

	player1score.renderTexture(gRenderer, SCREEN_WIDTH / 4, 20);

	player2score.renderTexture(gRenderer, 3 * SCREEN_WIDTH / 4, 20);

	paddle1->drawPaddle(gRenderer);

	paddle2->drawPaddle(gRenderer);

	ball->drawBall(gRenderer);

	SDL_RenderPresent(gRenderer);
}


void Game::gameLoop()
{
	InitGame();
	InitObject();
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			GetInput();
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		HandleInput();

		UpdateObjects();

		Collision collision;
		collision.HandleCollision(*ball, *paddle1, *paddle2);

		render();

	}
	close();
}
