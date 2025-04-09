#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "GameState.h"
namespace pong
{
	class Game;

	class Title : public GameState
	{
	public:
		Title		(Game& game);
		void		enter(SDL_Renderer* renderer, TTF_Font* font)	override;
		void		exit()											override;
		void		handleEvent(SDL_Event& e)						override;
		void		update(float deltaTime)							override;
		void		render()										override;
	private:
		SDL_Renderer* mRenderer;
		TTF_Font* mFont;
		Game& mGame;
		LoadTexture mInstructionsForP1;
		LoadTexture mInstructionsForP2;
		LoadTexture mInstructionsToBegin;
		LoadTexture mInstructionsForQuit;
		LoadTexture mTitleScreen;
	};
}

#endif // !TITLE_SCREEN_H