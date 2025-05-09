#ifndef COURT_SCREEN_H
#define COURT_SCREEN_H


#include "GameBase.h"
#include "GameState.h"
#include "Paddle.h"
#include "Ball.h"
#include "Collision.h"
#include "Particle.h"

namespace pong
{
	enum CourtIndex
	{
		Court_Resume,
		Court_Quit,
		totalCourtMenu = 3
	};

	class Game;

	class Court : public GameState
	{
	public:
		Court(Game& game, SDL_Renderer* renderer, TTF_Font* font);
		~Court();
		void			enter()												override;
		void			exit()												override;
		void			handleEvent(SDL_Event& e)							override;
		void			update(float deltaTime)								override;
		void			render()											override;
		void RenderParticles();
		void			RenderCourtMenu();
		void			LoadMedia();
		void			updatePlayerScore();
		void			updateGameObjects(float& mTime);
		void			handleInput();
	private:
		void LoadText(LoadTexture& normal, LoadTexture& selected,
			const std::string& content, SDL_Color normalColor, SDL_Color selectedColor);
		Game& mGame;
		SDL_Renderer* mRenderer;
		TTF_Font* mFont;

		Sound mBallHitPaddle;
		Sound mBallHitWall;
		Sound mSFX;

		LoadTexture		mBackgroundTexture;
		LoadTexture		mDefaultBackground;
		LoadTexture		mPausedText;
		SDL_Rect		mSpriteClips[3];
		LoadTexture		mSpriteSheet;
		LoadTexture		player1score;
		LoadTexture		player2score;

		LoadTexture		mResumeTextNormal;
		LoadTexture 	mQuitTextNormal;
		LoadTexture		mResumeTextSelected;
		LoadTexture		mQuitTextSelected;

		LoadTexture		mParticleTexture;
		LoadTexture		mShimmerTexture;
		
		Collision collision;
		Paddle* paddle1;
		Paddle* paddle2;
		Ball* ball;

		Particle* particles[TOTAL_PARTICLES];
		int	mSelectedMenuIndex;
		bool	mIsPaused;
		int	mVolume;
		int	mScore;
	};
}

#endif // !COURT_SCREEN_H