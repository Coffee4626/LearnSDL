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
	if (!p1message.LoadFromRenderedText(std::string("Player 1 wins"), mFont, color, mRenderer))
	{
		std::cout << "Failed to load win message for p1" << std::endl;
		return;
	}
	if (!p2message.LoadFromRenderedText(std::string("Player 2 wins"), mFont, color, mRenderer))
	{
		std::cout << "Failed to load win message for p2" << std::endl;
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
}

void End::update(float deltaTime)
{

}

void End::render()
{
	const auto& scores = mGame.getPlayerScores();
	if (scores[0] > 1)
	{
		p1message.renderTexture(mRenderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	else p2message.renderTexture(mRenderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}
