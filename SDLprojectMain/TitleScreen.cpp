#include "TitleScreen.h"
#include "StateManager.h"
#include "Game.h"
using namespace pong;

Title::Title(Game& game, SDL_Renderer* renderer, TTF_Font* font) :
	mGame(game),
	mRenderer(renderer),
	mFont(font),
	mSelectedMenuIndex(0)
{
	LoadMedia();
}
Title::~Title()
{
	mPlayTextNormal.Free();
	mHelpTextNormal.Free();
	mQuitTextNormal.Free();
	mPlayTextSelected.Free();
	mHelpTextSelected.Free();
	mQuitTextSelected.Free();
}
void Title::enter()
{

}

void Title::LoadMedia()
{
	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
	//If line is not selected, display in white
	mPlayTextNormal.LoadFromRenderedText(std::string("Play"), mFont, white, mRenderer);

	mHelpTextNormal.LoadFromRenderedText(std::string("Help"), mFont, white, mRenderer);

	mQuitTextNormal.LoadFromRenderedText(std::string("Quit"), mFont, white, mRenderer);

	//If line is selected, display in yellow
	SDL_Color yellow = { 0xFF, 0xFF, 0x00, 0xFF };
	mPlayTextSelected.LoadFromRenderedText(std::string("Play"), mFont, yellow, mRenderer);

	mHelpTextSelected.LoadFromRenderedText(std::string("Help"), mFont, yellow, mRenderer);

	mQuitTextSelected.LoadFromRenderedText(std::string("Quit"), mFont, yellow, mRenderer);

	//Title screen image
	mTitleScreen.LoadFromFile("Assets/Title.png", mRenderer);

	//Title screen BGM and sound fx
	//mBGM = Mix_LoadMUS("Assets/MenuBGM.wav");
	//mMenuSFX = Mix_LoadWAV("Assets/MenuScrollSound.wav");

	std::cout << "Title screen loaded successfully" << std::endl;
}

void Title::exit()
{
	//Freeing text
	mPlayTextNormal.Free();
	mPlayTextSelected.Free();
	mHelpTextNormal.Free();
	mHelpTextSelected.Free();
	mQuitTextNormal.Free();
	mQuitTextSelected.Free();
	std::cout << "Title resources freed, exited" << std::endl;
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
			//Mix_PlayChannel(-1, mMenuSFX, 0);
			break;
		}
		case SDLK_UP:
		{
			mSelectedMenuIndex = (mSelectedMenuIndex - 1 + 3) % 3;
			//Mix_PlayChannel(-1, mMenuSFX, 0);
			break;
		}
		case SDLK_RETURN:
		{
			if (mSelectedMenuIndex == MenuIndex::play)
			{
				std::cout << "Play button selected" << std::endl;
				RequestChangeScene(SceneType::COURT_SCREEN);
			}
			else if (mSelectedMenuIndex == MenuIndex::help)
			{
				std::cout << "Help button selected" << std::endl;
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