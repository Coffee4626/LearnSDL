#include "HelpScreen.h"
#include "TitleScreen.h"
#include "Game.h"

using namespace pong;
Help::Help(Game& game) : 
	mGame(game),
	mRenderer(nullptr),
	mFont(nullptr)
{
	//...
}

void Help::enter(SDL_Renderer* renderer, TTF_Font* font)
{
	this->mRenderer = renderer;
	this->mFont = font;
	SDL_Color color = { 0x00, 0x00, 0x00, 0xFF };
	if (!mInstructionsForP1.LoadFromRenderedText(std::string("Left Player uses W and S keys"), mFont, color, mRenderer))
	{
		std::cout << "Unable to load instructions for player 1" << std::endl;
		return;
	}
	if (!mInstructionsForP2.LoadFromRenderedText(std::string("Right Player uses Up and Down arrow keys"), mFont, color, mRenderer))
	{
		std::cout << "Unable to load instructions for player 2" << std::endl;
		return;
	}

}

void Help::exit()
{
	mInstructionsForP1.Free();
	mInstructionsForP2.Free();
	mRenderer = nullptr;
	mFont = nullptr;
}

void Help::handleEvent(SDL_Event& event)
{

}

void Help::update(float deltaTime)
{

}

void Help::render()
{

}