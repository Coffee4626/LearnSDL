#ifndef RESULT_SCREEN_H
#define RESULT_SCREEN_H

#include "GameBase.h"
#include "GameState.h"

class End : public GameState
{
public:
	End();
	void enter(SDL_Renderer* renderer, TTF_Font* font);
	void exit();
	void handleEvent(SDL_Event& event);
	void update();
	void render();
	bool checkChangeState();
	SceneType getNextScene();
private:
	SDL_Renderer*	mRenderer;
	TTF_Font*		mFont;
	LoadTexture		p1message;
	LoadTexture		p2message;
	bool			changeState;
};

#endif // !RESULT_SCREEN_H

