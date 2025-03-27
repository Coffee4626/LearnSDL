#ifndef COURT_SCREEN_H
#define COURT_SCREEN_H


#include "GameBase.h"
#include "GameState.h"
#include "Paddle.h"
#include "Ball.h"
#include "Collision.h"

class Court : public GameState
{
public:
	Court();
	void			enter(SDL_Renderer* renderer, TTF_Font* font)		override;
	void			exit()												override;
	void			handleEvent(SDL_Event &e)							override;
	void			update()											override;
	void			render()											override;
	bool			checkChangeState()									override;
	SceneType		getNextScene()										override;
	void			updatePlayerScore();
	void			updateGameObjects();
	void			handleInput();
private:
	Uint32			tickcounts;
	SDL_Renderer*	mRenderer;
	TTF_Font*		playerScore;
	LoadTexture		mBackgroundTexture;
	LoadTexture		player1score;
	LoadTexture		player2score;
	Collision		collision;
	Paddle*			paddle1;
	Paddle*			paddle2;
	Ball*			ball;
	float			deltaTime;
	int				p1score;
	int				p2score;
};

#endif // !COURT_SCREEN_H
