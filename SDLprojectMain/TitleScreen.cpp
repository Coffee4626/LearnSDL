#include "TitleScreen.h"
#include "CourtScreen.h"
#include "game.h"
using namespace pong;

Title::Title(Game& game) : 
	mGame(game),
	mRenderer(nullptr),
	mFont(nullptr)
{
	//...
}
void Title::enter(SDL_Renderer* renderer, TTF_Font* font)
{
	this->mRenderer = renderer;
	this->mFont = font;
	SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };
	if (!mInstructionsForP1.LoadFromRenderedText(std::string("Left Player uses W and S keys"), mFont, color, mRenderer))
	{
		std::cout << "Unable to load instructions for p1" << std::endl;
		return;
	}
	if (!mInstructionsForP2.LoadFromRenderedText(std::string("Right Player uses UP and DOWN keys"), mFont, color, mRenderer))
	{
		std::cout << "Unable to load instructions for p2" << std::endl;
		return;
	}
	if (!mInstructionsToBegin.LoadFromRenderedText(std::string("Press ENTER to begin playing"), mFont, color, mRenderer))
	{
		std::cout << "Unable to load instructions to play" << std::endl;
		return;
	}
	if (!mInstructionsForQuit.LoadFromRenderedText(std::string("Press ESC to quit"), mFont, color, mRenderer))
	{
		std::cout << "Unable to load instructions to quit" << std::endl;
		return;
	}
	if (!mTitleScreen.LoadFromFile(std::string("Title.png"), mRenderer))
	{
		std::cout << "Unable to load title screen image" << std::endl;
		return;
	}
}

void Title::exit()
{
	mInstructionsForP1.Free();
	mInstructionsForP2.Free();
	mInstructionsToBegin.Free();
	mInstructionsForQuit.Free();
	std::cout << "Title resources freed" << std::endl;
}

void Title::handleEvent(SDL_Event& event)
{
	//Press enter to move from title to game screen
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
	{
		mGame.ChangeState(std::make_shared<Court>(mGame));
	}
}


void Title::update(float deltaTime)
{
	//...
}

void Title::render()
{
	mInstructionsForP1.renderTexture(mRenderer, SCREEN_WIDTH / 3.5, SCREEN_HEIGHT / 5);
	mInstructionsForP2.renderTexture(mRenderer, SCREEN_WIDTH / 4, 2 * SCREEN_HEIGHT / 5);
	mInstructionsToBegin.renderTexture(mRenderer, SCREEN_WIDTH / 3.5, 3 * SCREEN_HEIGHT / 5);
	mInstructionsForQuit.renderTexture(mRenderer, SCREEN_WIDTH / 2.7, 4 * SCREEN_HEIGHT / 5);
}
