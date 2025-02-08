
#ifndef LOAD_MEDIA_H
#define LOAD_MEDIA_H
#include "gameBase.h"

SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE);

SDL_Renderer* createRenderer(SDL_Window* window);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);



#endif // !LOAD_MEDIA_H
