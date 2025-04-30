#ifndef COURT_SCREEN_H
#define COURT_SCREEN_H


#include "GameBase.h"
#include "GameState.h"
#include "Paddle.h"
#include "Ball.h"
#include "Collision.h"

namespace pong
{
	class Game;

	enum CourtMenu
	{
		Courtresume,
		Courtsettings,
		Courtquit,
		totalCourtMenu = 3
	};

	class Court : public GameState
	{
	public:
		Court(Game& game, SDL_Renderer* renderer, TTF_Font* font);
		void			enter()												override;
		void			exit()												override;
		void			handleEvent(SDL_Event& e)							override;
		void			update(float deltaTime)								override;
		void			render()											override;
		void			DisplayCourtMenu();
		void			LoadMedia();
		void			updatePlayerScore();
		void			updateGameObjects(float& mTime);
		void			handleInput();
	private:
		Game& mGame;
		SDL_Renderer* mRenderer;
		TTF_Font* mFont;

		Sound mBallHitPaddle;
		Sound mBallHitWall;

		LoadTexture		mBackgroundTexture;
		LoadTexture		mDefaultBackground;
		LoadTexture		mPausedText;
		SDL_Rect		mSpriteClips[3];
		LoadTexture		mSpriteSheet;
		LoadTexture		player1score;
		LoadTexture		player2score;

		LoadTexture		mResumeTextNormal;
		LoadTexture		mSettingsTextNormal;
		LoadTexture 	mQuitTextNormal;
		LoadTexture		mResumeTextSelected;
		LoadTexture		mSettingsTextSelected;	
		LoadTexture		mQuitTextSelected;
		LoadTexture		mVolumeTextNormal;
		LoadTexture		mVolumeTextSelected;
		LoadTexture		mScoreTextNormal;
		LoadTexture		mScoreTextSelected;
		
		Collision collision;
		Paddle* paddle1;
		Paddle* paddle2;
		Ball* ball;
		int mSelectedMenuIndex;
		bool			mIsPaused;
		bool			mSettingsMenuOpen;
	};
}

#endif // !COURT_SCREEN_H