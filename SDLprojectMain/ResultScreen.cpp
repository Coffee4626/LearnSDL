#include "ResultScreen.h"

End::End()
{

}

void End::enter(SDL_Renderer* renderer, TTF_Font* font)
{
	SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };
	if (!p1message.LoadFromRenderedText(std::string("Player 1 wins"), font, color, renderer))
	{
		std::cout << "Failed to load win message for p1" << std::endl;
		return;
	}
	if (!p2message.LoadFromRenderedText(std::string("Player 2 wins"), font, color, renderer))
	{
		std::cout << "Failed to load win message for p2" << std::endl;
		return;
	}
	this->mRenderer = renderer;
	this->mFont = font;
}

void End::exit()
{
	p1message.Free();
	p2message.Free();
	mRenderer = NULL;
	mFont = NULL;
}

void End::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
	{
		changeState = true;
	}
}

void End::update()
{

}

void End::render()
{
	if (p1win == true)
	{
		p1message.renderTexture(mRenderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	else p2message.renderTexture(mRenderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

bool End::checkChangeState()
{
	return changeState;
}

SceneType End::getNextScene()
{
	return SceneType::COURT_SCREEN;
}