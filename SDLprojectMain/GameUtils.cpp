#include "GameUtils.h"


void DisplayPlayerScore(LoadTexture gTextTexture,
	LoadTexture gScoreTexture,
	SDL_Color color,
	SDL_Renderer* renderer,
	TTF_Font* font,
	const int& score, float x, float y)
{
	std::string scoreText = std::to_string(score);

	if (!gScoreTexture.LoadFromRenderedText(scoreText, font, color, renderer))
	{
		std::cout << "Failed to render score texture!" << std::endl;
	}

	gScoreTexture.renderTexture(renderer, x, y);
}