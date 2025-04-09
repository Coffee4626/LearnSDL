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

	class Court : public GameState
	{
	public:
		Court			(Game& game);
		void			enter(SDL_Renderer* renderer, TTF_Font* font)		override;
		void			exit()												override;
		void			handleEvent(SDL_Event& e)							override;
		void			update(float deltaTime)								override;
		void			render()											override;
		void			updatePlayerScore();
		void			updateGameObjects(float &mTime);
		void			handleInput();
	private:
		Game&			mGame;
		SDL_Renderer*	mRenderer;
		TTF_Font*		mFont;
		LoadTexture		mBackgroundTexture;
		LoadTexture		player1score;
		LoadTexture		player2score;
		Collision		collision;
		Paddle*			paddle1;
		Paddle*			paddle2;
		Ball*			ball;
	};
}

#endif // !COURT_SCREEN_H