#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include "GameBase.h"
#include "LoadMedia.h"

void DisplayPlayerScore(LoadTexture gTextTexture,
	LoadTexture gScoreTexture,
	SDL_Color color,
	SDL_Renderer* renderer,
	TTF_Font* font,
	const int& score, float x, float y);

#endif // !GAME_UTILS_H
