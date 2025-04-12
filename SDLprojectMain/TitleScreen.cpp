#include "TitleScreen.h"
#include "CourtScreen.h"
#include "game.h"
using namespace pong;

Title::Title(Game& game) : 
	mGame(game),
	mRenderer(nullptr),
	mFont(nullptr),
	mSelectedMenuIndex(0)
{
	//...
}
void Title::enter(SDL_Renderer* renderer, TTF_Font* font)
{
	this->mRenderer = renderer;
	this->mFont = font;
	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
	//If line is not selected, display in white
	if (!mPlayTextNormal.LoadFromRenderedText(std::string("Play"), mFont, white, mRenderer))
	{
		std::cout << "Unable to load play text unselected for p1" << std::endl;
		return;
	}
	if (!mHelpTextNormal.LoadFromRenderedText(std::string("Help"), mFont, white, mRenderer))
	{
		std::cout << "Unable to load instructions for p1" << std::endl;
		return;
	}
	if (!mQuitTextNormal.LoadFromRenderedText(std::string("Quit"), mFont, white, mRenderer))
	{
		std::cout << "Unable to load instructions for p1" << std::endl;
		return;
	}
	//If line is selected, display in yellow
	SDL_Color yellow = { 0xFF, 0xFF, 0x00, 0xFF };
	if (!mPlayTextSelected.LoadFromRenderedText(std::string("Play"), mFont, yellow, mRenderer))
	{
		std::cout << "Unable to load instructions for p1" << std::endl;
		return;
	}
	if (!mHelpTextSelected.LoadFromRenderedText(std::string("Help"), mFont, yellow, mRenderer))
	{
		std::cout << "Unable to load instructions for p1" << std::endl;
		return;
	}
	if (!mQuitTextSelected.LoadFromRenderedText(std::string("Quit"), mFont, yellow, mRenderer))
	{
		std::cout << "Unable to load instructions for p1" << std::endl;
		return;
	}
	//Title screen image
	if (!mTitleScreen.LoadFromFile("Assets/Title4.png", mRenderer))
	{
		std::cout << "Unable to load title screen image" << std::endl;
		return;
	}
}

void Title::exit()
{
	mPlayTextNormal.Free();
	mPlayTextSelected.Free();
	mHelpTextNormal.Free();
	mHelpTextSelected.Free();
	mQuitTextNormal.Free();
	mQuitTextSelected.Free();
	std::cout << "Title resources freed" << std::endl;
}

void Title::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_DOWN:
			{
				mSelectedMenuIndex = (mSelectedMenuIndex + 1) % 3;
				break;
			}
			case SDLK_UP:
			{
				mSelectedMenuIndex = (mSelectedMenuIndex - 1 + 3) % 3;
				break;
			}
			case SDLK_RETURN:
			{
				if (mSelectedMenuIndex == MenuIndex::play)
				{
					std::cout << "Play button selected" << std::endl;
					mGame.ChangeState(std::make_shared<Court>(mGame));
				}
				else if (mSelectedMenuIndex == MenuIndex::help)
				{
					std::cout << "Help button selected" << std::endl;
					//mGame.ChangeState(std::make_shared<Help>(mGame));
				}
				else mGame.Quit();
				break;
			}
		}
	}
}


void Title::update(float deltaTime)
{
	//...
}

void Title::render()
{
	int temp = SCREEN_HEIGHT / 3;
	int yOffSet = 50;
	mTitleScreen.renderTexture(mRenderer, 0, 0);
	if (mSelectedMenuIndex == 0)
	{
		mPlayTextSelected.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - mPlayTextSelected.getWidth(), temp);
	}
	else mPlayTextNormal.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - mPlayTextSelected.getWidth(), temp);

	if (mSelectedMenuIndex == 1)
	{
		mHelpTextSelected.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - mHelpTextSelected.getWidth(), temp + yOffSet);
	}
	else mHelpTextNormal.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - mHelpTextSelected.getWidth(), temp + yOffSet);

	if (mSelectedMenuIndex == 2)
	{
		mQuitTextSelected.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - mQuitTextSelected.getWidth(), temp + 2 * yOffSet);
	}
	else mQuitTextNormal.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - mQuitTextSelected.getWidth(), temp + 2 * yOffSet);
}
