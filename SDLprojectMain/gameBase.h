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

namespace pong
{
	const int SCREEN_WIDTH = 1400;
	const int SCREEN_HEIGHT = 800;

	const float FPS = 60;
	const float FrameDelay = 1000.0f / FPS;

	enum buttons
	{
		left_paddle_up,
		left_paddle_down,
		right_paddle_up,
		right_paddle_down,
		total_paddle = 4,
	};

	enum PlayerIndex
	{
		first,
		second,
		total = 2,
	};

};




void logErrorAndExit(const char* msg, const char* error);

#endif // !GAME_BASE_H
