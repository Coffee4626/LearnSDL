#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "GameBase.h"
#include <memory>

namespace pong
{
	enum class SceneType
	{
		TITLE_SCREEN,
		COURT_SCREEN,
		RESULT_SCREEN
	};

	class GameStateManager;

	class GameState
	{
	public:
		virtual void enter() = 0;
		virtual void exit() = 0;
		virtual void handleEvent(SDL_Event& e) = 0;
		virtual void update(float deltaTime) = 0;
		virtual void render() = 0;

		void SetStateManager(GameStateManager* manager);
		void RequestChangeScene(SceneType newScene);

		GameStateManager* mStateManager;
	};
}

#endif // !GAME_STATE_H