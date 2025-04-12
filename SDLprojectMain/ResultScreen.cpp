#include "CourtScreen.h"
#include "ResultScreen.h"
#include "Game.h"
using namespace pong;
End::End(Game& game) :
	mGame(game),
	mRenderer(nullptr),
	mFont(nullptr)
{
	
}

void End::enter(SDL_Renderer* renderer, TTF_Font* font)
{
	this->mRenderer = renderer;
	this->mFont = font;
	SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };
	if (!p1message.LoadFromFile("Assets/Left player win.png", mRenderer))
	{
		std::cout << "Unable to load win message for p1" << std::endl;
		return;
	}
	if (!p2message.LoadFromFile("Assets/Right player win.png", mRenderer))
	{
		std::cout << "Unable to load win message for p2" << std::endl;
		return;
	}
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
		mGame.ChangeState(std::make_shared<Court>(mGame));
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	{
		mGame.Quit();
	}
}

void End::update(float deltaTime)
{

}

void End::render()
{
	const auto& scores = mGame.getPlayerScores();
	if (scores[0] > 2)
	{
		p1message.renderTexture(mRenderer, 0, 0);
	}
	else p2message.renderTexture(mRenderer, 0, 0);
}
