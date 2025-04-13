#ifndef HELP_SCREEN_H
#define HELP_SCREEN_H

#include "GameState.h"
namespace pong
{
	class Game;

	class Help : public GameState
	{
	public:
		Help(Game& game);
		void enter(SDL_Renderer* renderer, TTF_Font* font)	override;
		void exit()											override;
		void handleEvent(SDL_Event& event)					override;
		void update(float deltaTime)						override;
		void render()										override;
	private:
		Game&			mGame;
		SDL_Renderer*	mRenderer;
		TTF_Font*		mFont;
		LoadTexture mInstructionsForP1;
		LoadTexture mInstructionsForP2;
	};
}

#endif // !HELP_SCREEN_H
