#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "GameState.h"

class Title : public GameState
{
public:
	Title();
	void		enter(SDL_Renderer* renderer, TTF_Font* font)	override;
	void		exit()											override;
	void		handleEvent(SDL_Event& e)						override;
	void		update()										override;
	void		render()										override;
	bool		checkChangeState()								override;
	SceneType	getNextScene()									override;
private:
	LoadTexture mInstructionsForP1;
	LoadTexture mInstructionsForP2;
	LoadTexture mInstructionsToBegin;
	//LoadTexture mInstructionsToConfig;
	//LoadTexture mBackgroundTexture;
	LoadTexture mInstructionsForQuit;
	SDL_Renderer* mRenderer;
	bool changeState;
};

#endif // !TITLE_SCREEN_H
