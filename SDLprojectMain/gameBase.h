#ifndef GAME_BASE_H
#define GAME_BASE_H

#include <SDL.h>
#include <cmath>
#include <iostream>
#include <string>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "LoadTexture.h"

const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 800;

void logErrorAndExit(const char* msg, const char* error);

#endif // !GAME_BASE_H
