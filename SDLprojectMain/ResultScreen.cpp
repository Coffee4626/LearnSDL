#include "ResultScreen.h"
#include "StateManager.h"
#include "Game.h"
using namespace pong;
End::End(Game& game, SDL_Renderer* renderer, TTF_Font* font) :
	mGame(game),
	mRenderer(renderer),
	mFont(font)
{
	std::cout << "Result constructor called" << std::endl;
	p1message.LoadFromFile("Assets/Left player win.png", mRenderer);
	p2message.LoadFromFile("Assets/Right player win.png", mRenderer);
}

void End::enter()
{

}

void End::exit()
{
	std::cout << "End screen resources freed" << std::endl;
}

void End::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
	{
		RequestChangeScene(SceneType::COURT_SCREEN);
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