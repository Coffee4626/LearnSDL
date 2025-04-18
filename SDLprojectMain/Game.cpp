#include "Game.h"
#include "TitleScreen.h"
using namespace pong;

Game::Game() : gWindow(nullptr), 
	gRenderer(nullptr), 
	gFont(nullptr), 
	gPlayerScores({0, 0}), 
	quit(false)
{
	
}

Game::~Game()
{
	gFont = nullptr;
	gRenderer = nullptr;
	gWindow = nullptr;
	
	TTF_CloseFont(gFont);
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

void Game::InitSDL()
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
	
	if (IMG_Init(IMG_INIT_PNG || IMG_INIT_JPG) == 0)
	{
		std::cout << "Unable to initialize IMG: " << IMG_GetError() << std::endl;
		return;
	}

	if (Mix_Init(MIX_INIT_MP3) == 0)
	{
		std::cout << "Unable to initialize MIX: " << Mix_GetError() << std::endl;
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

	gFont = TTF_OpenFont("Assets/DejaVuSansMono.ttf", 40);
	if (gFont == NULL)
	{
		std::cout << "Unable to load a font for the application: " << TTF_GetError() << std::endl;
		return;
	}
	std::cout << "Initialization complete" << std::endl;
}


void Game::ChangeState(State mState)
{
	if (mState == NULL)
	{
		std::cout << "Unable to set active scene as null" << std::endl;
		return;
	}
	if (gState)
	{
		gState->exit();
	}
	gState = mState;
	gState->enter(gRenderer, gFont);
}

void Game::Quit()
{
	quit = true;
	std::cout << "Game quitted" << std::endl;
}

void Game::GameLoop()
{
	InitSDL();
	ChangeState(std::make_shared<Title>(*this));	
	Uint32 previousTime = SDL_GetTicks();
	float lag = 0;
	while (!quit)
	{
		Uint32 currentTime = SDL_GetTicks();
		float elapsedTime = currentTime - previousTime;
		previousTime = currentTime;
		lag += elapsedTime;
		while (SDL_PollEvent(&gEvent))
		{
			if (gEvent.type == SDL_QUIT)
			{
				Quit();
			}
			gState->handleEvent(gEvent);
		}
		while (lag >= FrameDelay)
		{
			lag -= FrameDelay;
			gState->update(FrameDelay);
		}
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);
		gState->render();
		SDL_RenderPresent(gRenderer);
	}
}