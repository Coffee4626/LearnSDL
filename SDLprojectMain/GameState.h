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
	class GameState
	{
	public:
		virtual void enter(SDL_Renderer* renderer, TTF_Font* font) = 0;
		virtual void exit() = 0;
		virtual void handleEvent(SDL_Event& e) = 0;
		virtual void update(float deltaTime) = 0;
		virtual void render() = 0;
	};
typedef std::shared_ptr<GameState> State;
}

#endif // !GAME_STATE_H