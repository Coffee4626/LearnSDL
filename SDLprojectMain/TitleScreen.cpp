#include "TitleScreen.h"
Title::Title()
{
	changeState = false;
}

void Title::enter(SDL_Renderer* renderer, TTF_Font* font)
{
	SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };
	if (!mInstructionsForP1.LoadFromRenderedText(std::string("Left Player uses W and S keys"), font, color, renderer))
	{
		std::cout << "Failed to load instructions for p1" << std::endl;
		return;
	}
	if (!mInstructionsForP2.LoadFromRenderedText(std::string("Right Player uses UP and DOWN keys"), font, color, renderer))
	{
		std::cout << "Failed to load instructions for p2" << std::endl;
		return;
	}
	if (!mInstructionsToBegin.LoadFromRenderedText(std::string("Press ENTER to begin playing"), font, color, renderer))
	{
		std::cout << "Failed to load instructions to play" << std::endl;
		return;
	}
	if (!mInstructionsForQuit.LoadFromRenderedText(std::string("Press ESC to quit"), font, color, renderer))
	{
		std::cout << "Failed to load instructions to quit" << std::endl;
		return;
	}
	this->mRenderer = renderer;
}

void Title::exit()
{
	mInstructionsForP1.Free();
	mInstructionsForP2.Free();
	mInstructionsToBegin.Free();
	mInstructionsForQuit.Free();
}

void Title::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
	{
		changeState = true;
	}
}

bool Title::checkChangeState()
{
	return changeState;
}

void Title::update()
{

}

void Title::render()
{
	mInstructionsForP1.renderTexture(mRenderer, SCREEN_WIDTH / 3.5, SCREEN_HEIGHT / 5);
	mInstructionsForP2.renderTexture(mRenderer, SCREEN_WIDTH / 4, 2 * SCREEN_HEIGHT / 5);
	mInstructionsToBegin.renderTexture(mRenderer, SCREEN_WIDTH / 3.5, 3 * SCREEN_HEIGHT / 5);
	mInstructionsForQuit.renderTexture(mRenderer, SCREEN_WIDTH / 2.7, 4 * SCREEN_HEIGHT / 5);
}

SceneType Title::getNextScene()
{
	return SceneType::COURT_SCREEN;
}
