#ifndef RESULT_SCREEN_H
#define RESULT_SCREEN_H

#include "GameBase.h"
#include "GameState.h"
namespace pong
{
	class Game;

	class End : public GameState
	{
	public:
		End(Game& game, SDL_Renderer* renderer, TTF_Font* font);
		~End();
		void enter()	override;
		void exit()											override;
		void handleEvent(SDL_Event& event)					override;
		void update(float deltaTime)						override;
		void render()										override;
	private:
		Game& mGame;
		SDL_Renderer* mRenderer;
		TTF_Font* mFont;
		LoadTexture		p1message;
		LoadTexture		p2message;
		int mScore;
	};
}

#endif // !RESULT_SCREEN_H