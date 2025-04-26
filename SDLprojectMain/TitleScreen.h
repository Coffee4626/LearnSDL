#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "GameState.h"
namespace pong
{
	class Game;

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
	private:
		SDL_Renderer* mRenderer;
		TTF_Font* mFont;
		Game& mGame;
		LoadTexture mPlayTextNormal;
		LoadTexture mPlayTextSelected;
		LoadTexture mHelpTextNormal;
		LoadTexture mHelpTextSelected;
		LoadTexture mQuitTextNormal;
		LoadTexture mQuitTextSelected;
		LoadTexture mTitleScreen;
		int mSelectedMenuIndex;
	};
}

#endif // !TITLE_SCREEN_H