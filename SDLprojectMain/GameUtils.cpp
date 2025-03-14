#include "GameUtils.h"

void DisplayPlayerScore(LoadTexture gTextTexture,
	LoadTexture gScoreTexture,
	SDL_Color color,
	SDL_Renderer* renderer,
	TTF_Font* font,
	const int& score)
{   
	gScoreTexture.renderTexture(renderer, SCREEN_WIDTH / 4, 20);

	if (gScoreTexture.LoadFromRenderedText(std::to_string(score), font, color, renderer))
	{
        gScoreTexture.renderTexture(renderer, SCREEN_WIDTH / 4, 20);
	}
}

SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (TTF_Init() == -1)
    {
        std::cout << "Failed to initialize TTF" << std::endl;
    }

    //full screen
    //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}
