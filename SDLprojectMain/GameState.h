#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "GameBase.h"

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

	virtual void handleEvent(SDL_Event &e) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool checkChangeState() = 0;
	virtual SceneType getNextScene() = 0;
	virtual ~GameState() {};

};

#endif // !GAME_STATE_H
