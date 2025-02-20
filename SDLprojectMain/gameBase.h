
#ifndef GAME_BASE_H
#define GAME_BASE_H

#include <SDL.h>
#include <cmath>
#include <iostream>
#include <string>
#include <SDL_image.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;



void logErrorAndExit(const char* msg, const char* error);

#endif // !GAME_BASE_H
