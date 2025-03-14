#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include "GameBase.h"



SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE);

SDL_Renderer* createRenderer(SDL_Window* window);

#endif // !GAME_UTILS_H
