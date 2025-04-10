#ifndef GAME_H
#define GAME_H
#include "GameState.h"
#include <array>

namespace pong
{
	class Game
	{
	public:
		Game();
		~Game();
		void GameLoop();
		void InitSDL();
		void Quit();
		void ChangeState(State mState);
		std::array<int, 2>& getPlayerScores()
		{
			return gPlayerScores;
		}
	private:
		SDL_Window*			gWindow;
		SDL_Renderer*		gRenderer;
		TTF_Font*			gFont;
		State				gState;
		SDL_Event			gEvent;
		std::array<int, 2> gPlayerScores;
		bool				quit;
 	};
	
};

#endif // !GAME_H
//0788080565