#include "TitleScreen.h"
#include "StateManager.h"
#include "Game.h"
using namespace pong;

Title::Title(Game& game, SDL_Renderer* renderer, TTF_Font* font) :
	mGame(game),
	mRenderer(renderer),
	mFont(font),
	mSelectedMenuIndex(0),
	mVolume(mGame.gSound.GetVolume()),
	mMaxScore(1),
	mSelectedSettingsMenuIndex(0)
{
	std::cout << "Title constructor called" << std::endl;
	LoadMedia();
}

Title::~Title()
{
	mTitleScreen.Free();
	mInstructionsForPlayers.Free();
	mInstructionsToPause.Free();
	//mInstructionsForPowerup.Free();

	mPlayTextNormal.Free();
	mHelpTextNormal.Free();
	mSettingsTextNormal.Free();
	mVolumeTextNormal.Free();
	mScoreTextNormal.Free();
	mQuitTextNormal.Free();

	mPlayTextSelected.Free();
	mHelpTextSelected.Free();
	mSettingsTextSelected.Free();
	mQuitTextSelected.Free();
	mVolumeTextSelected.Free();
	mScoreTextSelected.Free();

	mBGM.Free();
	mMenuSFX.Free();
	std::cout << "Title destructor called" << std::endl;
}
void Title::enter()
{
	mBGM.PlaySound(-1, 0, mGame.gSound.GetVolume());
	std::cout << "Entered Title screen" << std::endl;
}

void Title::LoadMedia()
{
	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
	//If line is not selected, display in white
	mPlayTextNormal.LoadFromRenderedText("Play", mFont, white, mRenderer);

	mHelpTextNormal.LoadFromRenderedText("Help", mFont, white, mRenderer);

	mSettingsTextNormal.LoadFromRenderedText("Settings", mFont, white, mRenderer);

	mQuitTextNormal.LoadFromRenderedText("Quit", mFont, white, mRenderer);

	mVolumeTextNormal.LoadFromRenderedText("Volume", mFont, white, mRenderer);

	mScoreTextNormal.LoadFromRenderedText("Max score", mFont, white, mRenderer);

	//If line is selected, display in yellow
	SDL_Color yellow = { 0xFF, 0xFF, 0x00, 0xFF };
	mPlayTextSelected.LoadFromRenderedText("Play", mFont, yellow, mRenderer);
	
	mHelpTextSelected.LoadFromRenderedText("Help", mFont, yellow, mRenderer);

	mSettingsTextSelected.LoadFromRenderedText("Settings", mFont, yellow, mRenderer);

	mQuitTextSelected.LoadFromRenderedText("Quit", mFont, yellow, mRenderer);

	mVolumeTextSelected.LoadFromRenderedText("Volume " + std::to_string(mGame.gSound.GetVolume() / 128 * 100), mFont, yellow, mRenderer);

	mScoreTextSelected.LoadFromRenderedText("Max score " + std::to_string(mGame.GetMaxScore()), mFont, { 0xFF, 0xFF, 0x00, 0xFF }, mRenderer);

	//Instructions for players
	mInstructionsForPlayers.LoadFromRenderedText("Left player uses W and S, Right player use Up and Down", mFont, white, mRenderer);
	//mInstructionsForPowerup.LoadFromRenderedText(std::string("Powerup: Press P"), mFont, white, mRenderer);
	mInstructionsToPause.LoadFromRenderedText("Pause: Press ESC in game", mFont, white, mRenderer);

	//Title screen image
	mTitleScreen.LoadFromFile("Assets/Title.png", mRenderer);

	//Title screen BGM and sound fx

	mBGM.LoadSound("Assets/MenuBGM.wav");
	mMenuSFX.LoadSound("Assets/MenuScrollSound.wav");
	
}

void Title::exit()
{
	std::cout << "Title screen exited" << std::endl;
}

void Title::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_DOWN:
			{
				if (mSettingsSelected == true)
				{
					mSelectedSettingsMenuIndex = (mSelectedSettingsMenuIndex + 1) % 2;
				}
				mSelectedMenuIndex = (mSelectedMenuIndex + 1) % MenuIndex::total_menu;
				mMenuSFX.PlaySound(-1, 0, mGame.gSound.GetVolume());
				break;
			}
			case SDLK_UP:
			{
				if (mSettingsSelected == true)
				{
					mSelectedSettingsMenuIndex = (mSelectedSettingsMenuIndex - 1 + 2) % 2;
					std::cout << mSelectedMenuIndex << std::endl;

				}
				mSelectedMenuIndex = (mSelectedMenuIndex - 1 + MenuIndex::total_menu) % MenuIndex::total_menu;
				std::cout << mSelectedMenuIndex << std::endl;
				mMenuSFX.PlaySound(-1, 0, mGame.gSound.GetVolume());
				break;
			}
			case SDLK_RIGHT:
			{
				mMenuSFX.PlaySound(-1, 0, mGame.gSound.GetVolume());
				if (mSettingsSelected == true && mSelectedSettingsMenuIndex == SettingsIndex::volume)
				{
					mVolume++;
					UpdateSettings();
				}
				if (mSettingsSelected == true && mSelectedSettingsMenuIndex == SettingsIndex::score)
				{
					mMaxScore++;
					UpdateSettings();
				}
				break;
			}
			case SDLK_LEFT:
			{
				mMenuSFX.PlaySound(-1, 0, mGame.gSound.GetVolume());
				if (mSettingsSelected == true && mSelectedSettingsMenuIndex == SettingsIndex::volume)
				{
					mVolume--;
					UpdateSettings();
				}
				if (mSettingsSelected == true && mSelectedSettingsMenuIndex == SettingsIndex::score)
				{
					mMaxScore--;
					UpdateSettings();
				}
				break;
			}
			case SDLK_RETURN:
			{
				if (mSelectedMenuIndex == MenuIndex::play && mHelpSelected == false && mSettingsSelected == false)
				{
					std::cout << "Play button selected" << std::endl;
					RequestChangeScene(SceneType::COURT_SCREEN);
				}
				if (mSelectedMenuIndex == MenuIndex::help && mHelpSelected == false && mSettingsSelected == false)
				{
					std::cout << "Help button selected" << std::endl;
					mSelectedMenuIndex = 0;
					mHelpSelected = true;
				}
				if (mSelectedMenuIndex == MenuIndex::settings && mHelpSelected == false && mSettingsSelected == false)
				{
					std::cout << "Settings button selected" << std::endl;
					mSelectedMenuIndex = 0;
					mSettingsSelected = true;
				}
				if (mSelectedMenuIndex == MenuIndex::quit && mHelpSelected == false && mSettingsSelected == false)
				{
					std::cout << "Quit button selected" << std::endl;
					mGame.Quit();
				}
				break;
			}
			case SDLK_ESCAPE:
			{
				if (mSettingsSelected == true)
				{
					mSettingsSelected = false;
				}
				if (mHelpSelected == true)
				{
					mHelpSelected = false;
				}
				break;
			}
		}
	}
}

void Title::UpdateSettings()
{
	if (mVolume > MAX_VOLUME)
	{
		mVolume = MAX_VOLUME;
	}
	if (mVolume < MIN_VOLUME)
	{
		mVolume = MIN_VOLUME;
	}
	mGame.gSound.SetVolume(mVolume);
	mVolumeTextSelected.LoadFromRenderedText("Volume " + 
		std::to_string((mGame.gSound.GetVolume() * 100) / 128), mFont, { 0xFF, 0xFF, 0x00, 0xFF }, mRenderer);

	if (mMaxScore > MAX_SCORE)
	{
		mMaxScore = MAX_SCORE;
	}
	if (mMaxScore < MIN_SCORE)
	{
		mMaxScore = MIN_SCORE;
	}
	mGame.SetMaxScore(mMaxScore);
	std::cout << mGame.GetMaxScore() << std::endl;
	mScoreTextSelected.LoadFromRenderedText("Max score " +
		std::to_string(mGame.GetMaxScore()), mFont, { 0xFF, 0xFF, 0x00, 0xFF }, mRenderer);
}

void Title::update(float deltaTime)
{

}

void Title::render()
{
	int height = SCREEN_HEIGHT / 3;
	int yOffSet = 50;
	mTitleScreen.renderTexture(mRenderer, 0, 0);

	if (mHelpSelected == true)
	{
		mInstructionsForPlayers.renderTexture(mRenderer, 
			SCREEN_WIDTH / 2 - mInstructionsForPlayers.getWidth() / 2, 
			SCREEN_HEIGHT / 2 - mInstructionsForPlayers.getHeight() / 2);
		mInstructionsToPause.renderTexture(mRenderer,
			SCREEN_WIDTH / 2 - mInstructionsToPause.getWidth() / 2,
			SCREEN_HEIGHT / 2 - mInstructionsToPause.getHeight() / 2 + yOffSet);
	}
	else if (mSettingsSelected == true)
	{
		if (mSelectedSettingsMenuIndex == SettingsIndex::volume)
		{
			mVolumeTextSelected.renderTexture(mRenderer,
				SCREEN_WIDTH / 2 - mVolumeTextNormal.getWidth() / 2,
				SCREEN_HEIGHT / 2 - mVolumeTextNormal.getHeight() / 2);
		}
		else
		{
			mVolumeTextNormal.renderTexture(mRenderer,
				SCREEN_WIDTH / 2 - mVolumeTextNormal.getWidth() / 2,
				SCREEN_HEIGHT / 2 - mVolumeTextNormal.getHeight() / 2);
		}
		if (mSelectedSettingsMenuIndex == SettingsIndex::score)
		{
			mScoreTextSelected.renderTexture(mRenderer,
				SCREEN_WIDTH / 2 - mScoreTextSelected.getWidth() / 2,
				SCREEN_HEIGHT / 2 - mScoreTextSelected.getHeight() / 2 + yOffSet);
		}
		else
		{
			mScoreTextNormal.renderTexture(mRenderer,
				SCREEN_WIDTH / 2 - mScoreTextNormal.getWidth() / 2,
				SCREEN_HEIGHT / 2 - mScoreTextNormal.getHeight() / 2 + yOffSet);
		}
	}
	else
	{
		if (mSelectedMenuIndex == MenuIndex::play)
		{
			mPlayTextSelected.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - mPlayTextSelected.getWidth(), height);
		}
		else mPlayTextNormal.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - mPlayTextSelected.getWidth(), height);

		if (mSelectedMenuIndex == MenuIndex::help)
		{
			mHelpTextSelected.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - mHelpTextSelected.getWidth(), height + yOffSet);
		}
		else mHelpTextNormal.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - mHelpTextSelected.getWidth(), height + yOffSet);
		
		if (mSelectedMenuIndex == MenuIndex::settings)
		{
			mSettingsTextSelected.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - mHelpTextSelected.getWidth(), height + 2 * yOffSet);
		}
		else mSettingsTextNormal.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - mHelpTextSelected.getWidth(), height + 2 * yOffSet);

		if (mSelectedMenuIndex == MenuIndex::quit)
		{
			mQuitTextSelected.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - mQuitTextSelected.getWidth(), height + 3 * yOffSet);
		}
		else mQuitTextNormal.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - mQuitTextSelected.getWidth(), height + 3 * yOffSet);
	}
}