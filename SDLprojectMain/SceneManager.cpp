#include "SceneManager.h"

SceneManager::SceneManager()
{
	gWindow = NULL;
	gRenderer = NULL;
	gFont = NULL;
	currentState = NULL;
	nextSceneType = SceneType::TITLE_SCREEN;
	quit = false;
}

void SceneManager::InitSDL()
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

	gFont = TTF_OpenFont("Assets/DejaVuSansMono.ttf", 40);
	if (gFont == NULL)
	{
		std::cout << "Unable to load a font for the application: " << TTF_GetError() << std::endl;
	}
	std::cout << "initialized complete" << std::endl;
}

void SceneManager::SetNextScene(SceneType nextScene) 
{
	nextSceneType = nextScene;
}

void SceneManager::InitGame()
{
	InitSDL();
	quit = false;
	ChangeState();
}

void SceneManager::ChangeState()
{
	// Clean up the current scene
	if (currentState) 
	{
		currentState->exit();
	}
	switch (nextSceneType) 
	{
	case SceneType::TITLE_SCREEN:
		currentState = new Title();
		break;
	case SceneType::COURT_SCREEN:
		currentState = new Court();
		break;
	case SceneType::RESULT_SCREEN:
		currentState = new End();
		break;
	default:
		break;
	}
	if (currentState) 
	{
		currentState->enter(gRenderer, gFont); 
		std::cout << "Scene changed" << std::endl;
	}
}


void SceneManager::QuitGame()
{
	currentState = NULL;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	TTF_CloseFont(gFont);
	gFont = NULL;

	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}


void SceneManager::MainLoop()
{
	InitGame();
	while (!quit)
	{
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			currentState->handleEvent(event);
		}

		currentState->update();
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);
		currentState->render();
		SDL_RenderPresent(gRenderer);

		if (currentState->checkChangeState())
		{
			SetNextScene(currentState->getNextScene());
			ChangeState();
		}
	}
}
