#include "Game.h"
using namespace pong;

Game::Game() : gWindow(nullptr),
gRenderer(nullptr),
gFont(nullptr),
gPlayerScores({ 0, 0 }),
quit(false),
gStateManager(nullptr)
{
	std::cout << "Game constructor called" << std::endl;
}

void Game::LoadSaveFile()
{
	SDL_RWops* SaveFile = SDL_RWFromFile("Settings/SaveData.bin", "r + b");
	if (SaveFile == nullptr)
	{
		std::cout << "Unable to open save file: " << SDL_GetError() << std::endl;
		SaveFile = SDL_RWFromFile("Settings/SaveData.bin", "w + b");
		if (SaveFile != nullptr)
		{
			std::cout << "Save file created" << std::endl;
			int defaultVolume = 128;
			int defaultScore = 10;

			SDL_RWwrite(SaveFile, &defaultVolume, sizeof(int), 1);
			SDL_RWwrite(SaveFile, &defaultScore, sizeof(int), 1);

			gSound.SetVolume(defaultVolume);
			gMaxScore = defaultScore;

			SDL_RWclose(SaveFile);
		}
		else 
		{
			std::cout << "Unable to open save file: " << SDL_GetError() << std::endl;
		}
	}
	else
	{
		std::cout << "Reading data from save file" << std::endl;
		int volume = 0;
		SDL_RWread(SaveFile, &volume, sizeof(int), 1);
		gSound.SetVolume(volume);
		int score = 0;
		SDL_RWread(SaveFile, &score, sizeof(int), 1);
		gMaxScore = score;
		SDL_RWclose(SaveFile);
	}
}

void Game::SaveData()
{
	SDL_RWops* SaveFile = SDL_RWFromFile("Settings/SaveData.bin", "w+b");
	if (SaveFile == nullptr) 
	{
		std::cout << "Unable to open save file: " << SDL_GetError() << std::endl;
	}
	else 
	{
		std::cout << "Writing data to save file" << std::endl;

		int volume = gSound.GetVolume();
		SDL_RWwrite(SaveFile, &volume, sizeof(int), 1);

		SDL_RWwrite(SaveFile, &gMaxScore, sizeof(int), 1);

		SDL_RWclose(SaveFile);
	}
}

Game::~Game()
{
	gTitleScreen.reset();
	gCourtScreen.reset();
	gResultScreen.reset();
	if (gStateManager) delete gStateManager;
	gStateManager = nullptr;

	gRenderer = nullptr;
	gWindow = nullptr;
	gSound.Free();
	Mix_CloseAudio();
	TTF_CloseFont(gFont);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gFont = nullptr;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::SetMaxScore(int maxScore)
{
	gMaxScore = maxScore;
}

int Game::GetMaxScore() const
{
	return gMaxScore;
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

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
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

	LoadSaveFile();

	gStateManager = new GameStateManager();
	InitScene();

	gStateManager->ChangeState(SceneType::TITLE_SCREEN);

	std::cout << "Initialization complete" << std::endl;
}

void Game::InitScene()
{
	gTitleScreen = std::make_shared<Title>(*this, gRenderer, gFont);
	gCourtScreen = std::make_shared<Court>(*this, gRenderer, gFont);
	gResultScreen = std::make_shared<End>(*this, gRenderer, gFont);

	gStateManager->LoadState(SceneType::TITLE_SCREEN, gTitleScreen);
	gStateManager->LoadState(SceneType::COURT_SCREEN, gCourtScreen);
	gStateManager->LoadState(SceneType::RESULT_SCREEN, gResultScreen);
}

void Game::Quit()
{
	SaveData();
	quit = true;
	std::cout << "Game quitted" << std::endl;
}

void Game::GameLoop()
{
	InitSDL();
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
			gStateManager->HandleEvent(gEvent);
		}
		while (lag >= FrameDelay)
		{
			lag -= FrameDelay;
			gStateManager->Update(FrameDelay);
		}
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);
		gStateManager->Render();
		SDL_RenderPresent(gRenderer);
	}
}