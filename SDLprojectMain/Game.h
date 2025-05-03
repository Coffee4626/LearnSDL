#ifndef GAME_H
#define GAME_H
#include "LoadSound.h"
#include "StateManager.h"
#include "GameState.h"
#include "TitleScreen.h"
#include "CourtScreen.h"
#include "ResultScreen.h"
#include <array>

namespace pong
{
	class Game
	{
	public:
		Game();
		~Game();
		void GameLoop();
		void LoadSaveFile();
		void SaveData();
		void InitScene();
		void InitSDL();
		void Quit();
		int GetMaxScore() const;
		void SetMaxScore(int maxScore);
		std::array<int, 2>& getPlayerScores() { return gPlayerScores; }

		Sound	gSound;
		int	gMaxScore;
	private:
		SDL_Window* gWindow;
		SDL_Renderer* gRenderer;
		TTF_Font* gFont;
		SDL_Event			gEvent;
		std::array<int, 2>	gPlayerScores;

		GameStateManager* gStateManager;
		std::shared_ptr<Title> gTitleScreen;
		std::shared_ptr<Court> gCourtScreen;
		std::shared_ptr<End> gResultScreen;

		bool	quit;

	};

};

#endif // !GAME_H