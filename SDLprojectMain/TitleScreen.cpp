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
	mMaxScore(mGame.GetMaxScore()),
	mSelectedSettingsMenuIndex(0)
{
	std::cout << "Title constructor called" << std::endl;
	LoadMedia();
}

Title::~Title()
{
	std::cout << "Title destructor called" << std::endl;
	mTitleScreen.Free();
	mInstructionsForPlayers.Free();
	mInstructionsToPause.Free();

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
}
void Title::enter()
{
	std::cout << "Entered Title screen" << std::endl;
	mBGM.StopSound(-1);
	mBGM.PlaySound(-1, 0, mGame.gSound.GetVolume());
	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
	SDL_Color yellow = { 0xFF, 0xFF, 0x00, 0xFF };
	mVolumeTextNormal.LoadFromRenderedText("Volume", mFont, white, mRenderer);
	mScoreTextNormal.LoadFromRenderedText("Max score", mFont, white, mRenderer);
	mVolumeTextSelected.LoadFromRenderedText("Volume " + std::to_string(mVolume * 100 / 128), mFont, yellow, mRenderer);
	mScoreTextSelected.LoadFromRenderedText("Max score " + std::to_string(mMaxScore), mFont, yellow, mRenderer);
}

void Title::exit()
{
	std::cout << "Title screen exited" << std::endl;
}

void Title::render()
{
	mTitleScreen.renderTexture(mRenderer, 0, 0);
	if (mHelpSelected)
	{
		RenderHelpState();
	}
	else if (mSettingsSelected == true)
	{
		RenderSettings();
	}
	else
	{
		RenderMainMenu();
	}
}

void Title::update(float deltaTime)
{

}

void Title::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_DOWN:
			NavigateMenu(1);
			break;
		case SDLK_UP:
			NavigateMenu(-1);
			break;
		case SDLK_RIGHT:
			AdjustSettings(1);
			break;
		case SDLK_LEFT:
			AdjustSettings(-1);
			break;
		case SDLK_RETURN:
			SelectMenuOption();
			break;
		case SDLK_ESCAPE:
			ExitSubMenu();
			break;
		}
	}
}

void Title::LoadMedia()
{
	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
	SDL_Color yellow = { 0xFF, 0xFF, 0x00, 0xFF };
	//Load menu and settings text
	LoadText(mPlayTextNormal, mPlayTextSelected, "Play", white, yellow);
	LoadText(mHelpTextNormal, mHelpTextSelected, "Help", white, yellow);
	LoadText(mSettingsTextNormal, mSettingsTextSelected, "Settings", white, yellow);
	LoadText(mQuitTextNormal, mQuitTextSelected, "Quit", white, yellow);
	LoadText(mSaveTextNormal, mSaveTextSelected, "Save", white, yellow);

	//Load instructions text
	mInstructionsForPlayers.LoadFromRenderedText(
		"Left player uses W and S, Right player use Up and Down", mFont, white, mRenderer);
	mInstructionsToPause.LoadFromRenderedText("Pause: Press ESC in game", mFont, white, mRenderer);

	//Load background and sound
	mTitleScreen.LoadFromFile("Assets/Title.png", mRenderer);
	mBGM.LoadSound("Assets/MenuBGM.wav");
	mMenuSFX.LoadSound("Assets/MenuScrollSound.wav");

}

void Title::LoadText(LoadTexture& normal, LoadTexture& selected,
	const std::string& content, SDL_Color normalColor, SDL_Color selectedColor)
{
	normal.LoadFromRenderedText(content, mFont, normalColor, mRenderer);
	selected.LoadFromRenderedText(content, mFont, selectedColor, mRenderer);
}


void Title::NavigateMenu(int direction)
{
	if (mSettingsSelected)
	{
		mSelectedSettingsMenuIndex = (mSelectedSettingsMenuIndex + direction + SettingsIndex::total_settings) % SettingsIndex::total_settings;
	}
	else
	{
		mSelectedMenuIndex = (mSelectedMenuIndex + direction + MenuIndex::total_menu) % MenuIndex::total_menu;
	}
	mMenuSFX.PlaySound(-1, 0, mGame.gSound.GetVolume());
}

void Title::AdjustSettings(int adjustment)
{
	mMenuSFX.PlaySound(-1, 0, mGame.gSound.GetVolume());
	if (mSettingsSelected)
	{
		if (mSelectedSettingsMenuIndex == SettingsIndex::volume)
		{
			mVolume += adjustment;
			UpdateSettings();
		}
		else if (mSelectedSettingsMenuIndex == SettingsIndex::score)
		{
			mMaxScore += adjustment;
			UpdateSettings();
		}
	}
}

void Title::SelectMenuOption()
{
	if (!mHelpSelected && !mSettingsSelected)
	{
		switch (mSelectedMenuIndex)
		{
		case MenuIndex::Title_Play:
			std::cout << "Play button selected" << std::endl;
			RequestChangeScene(SceneType::COURT_SCREEN);
			break;
		case MenuIndex::Title_Help:
			std::cout << "Help button selected" << std::endl;
			mSelectedMenuIndex = 0;
			mHelpSelected = true;
			break;
		case MenuIndex::Title_Settings:
			std::cout << "Settings button selected" << std::endl;
			mSelectedMenuIndex = 0;
			mSettingsSelected = true;
			break;
		case MenuIndex::Title_Quit:
			std::cout << "Quit button selected" << std::endl;
			mGame.Quit();
			break;
		}
	}
	else if (mSettingsSelected && mSelectedSettingsMenuIndex == SettingsIndex::save)
	{
		mGame.SaveData();
		mSettingsSelected = false;
	}
}

void Title::ExitSubMenu()
{
	if (mSettingsSelected)
	{
		mSettingsSelected = false;
	}
	else if (mHelpSelected)
	{
		mHelpSelected = false;
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
	mScoreTextSelected.LoadFromRenderedText("Max score " +
		std::to_string(mGame.GetMaxScore()), mFont, { 0xFF, 0xFF, 0x00, 0xFF }, mRenderer);
}

void Title::RenderHelpState()
{
	int yOffSet = 50;
	mInstructionsForPlayers.renderTexture(mRenderer,
		SCREEN_WIDTH / 2 - mInstructionsForPlayers.getWidth() / 2,
		SCREEN_HEIGHT / 2 - mInstructionsForPlayers.getHeight() / 2);
	mInstructionsToPause.renderTexture(mRenderer,
		SCREEN_WIDTH / 2 - mInstructionsToPause.getWidth() / 2,
		SCREEN_HEIGHT / 2 - mInstructionsToPause.getHeight() / 2 + yOffSet);
}

void Title::RenderSettings()
{
	int yOffSet = 50;
	RenderSettingOption(mVolumeTextNormal, mVolumeTextSelected, SettingsIndex::volume, 0);
	RenderSettingOption(mScoreTextNormal, mScoreTextSelected, SettingsIndex::score, yOffSet);
	RenderSettingOption(mSaveTextNormal, mSaveTextSelected, SettingsIndex::save, 2 * yOffSet);
}

void Title::RenderSettingOption(LoadTexture& normal, LoadTexture& selected, int index, int yOffset)
{
	if (mSelectedSettingsMenuIndex == index)
	{
		selected.renderTexture(mRenderer,
			SCREEN_WIDTH / 2 - selected.getWidth() / 2,
			SCREEN_HEIGHT / 2 - selected.getHeight() / 2 + yOffset);
	}
	else normal.renderTexture(mRenderer,
		SCREEN_WIDTH / 2 - normal.getWidth() / 2,
		SCREEN_HEIGHT / 2 - normal.getHeight() / 2 + yOffset);
}

void Title::RenderMainMenu()
{
	int height = SCREEN_HEIGHT / 3;
	int yOffSet = 50;

	RenderMainMenuOption(mPlayTextNormal, mPlayTextSelected, MenuIndex::Title_Play, height);
	RenderMainMenuOption(mHelpTextNormal, mHelpTextSelected, MenuIndex::Title_Help, height + yOffSet);
	RenderMainMenuOption(mSettingsTextNormal, mSettingsTextSelected, MenuIndex::Title_Settings, height + 2 * yOffSet);
	RenderMainMenuOption(mQuitTextNormal, mQuitTextSelected, MenuIndex::Title_Quit, height + 3 * yOffSet);
}

void Title::RenderMainMenuOption(LoadTexture& normal, LoadTexture& selected,
	int index, int yOffset)
{
	if (mSelectedMenuIndex == index)
	{
		selected.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - selected.getWidth(), yOffset);

	}
	else normal.renderTexture(mRenderer, 2 * SCREEN_WIDTH / 3 - normal.getWidth(), yOffset);
}