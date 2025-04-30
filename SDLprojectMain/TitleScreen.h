#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "GameState.h"
namespace pong
{
	class Game;

	enum SettingsIndex
	{
		volume,
		score,
		total_settings = 2
	};

	class Title : public GameState
	{
	public:
		Title(Game& game, SDL_Renderer* renderer, TTF_Font* font);
		~Title();
		void		enter()	override;
		void		exit()											override;
		void		handleEvent(SDL_Event& e)						override;
		void		update(float deltaTime)							override;
		void		render()										override;
		void		LoadMedia();
		void	UpdateSettings();
	private:
		Game& mGame;
		SDL_Renderer* mRenderer;
		TTF_Font* mFont;

		Sound mBGM;
		Sound mMenuSFX;

		LoadTexture mInstructionsForPlayers;
		LoadTexture mInstructionsToPause;
		//LoadTexture mInstructionsForPowerup;

		LoadTexture mPlayTextNormal;
		LoadTexture mPlayTextSelected;
		LoadTexture mHelpTextNormal;
		LoadTexture mHelpTextSelected;
		LoadTexture mSettingsTextNormal;
		LoadTexture mSettingsTextSelected;
		LoadTexture mQuitTextNormal;
		LoadTexture mQuitTextSelected;
		LoadTexture mTitleScreen;

		LoadTexture		mVolumeTextNormal;
		LoadTexture		mVolumeTextSelected;
		LoadTexture		mScoreTextNormal;
		LoadTexture		mScoreTextSelected;

		int mSelectedMenuIndex;
		int mSelectedSettingsMenuIndex;
		bool mHelpSelected = false;
		bool mSettingsSelected = false;
		int mVolume;
		int mMaxScore;
	};
}

#endif // !TITLE_SCREEN_H