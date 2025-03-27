#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "GameBase.h"
#include "GameState.h"
#include "TitleScreen.h"
#include "CourtScreen.h"
#include "ResultScreen.h"

class SceneManager
{
public:
	SceneManager();
	void InitSDL();
	void SetNextScene(SceneType nextSceneType);
	void InitGame();
	void ChangeState();
	void MainLoop();
	void QuitGame();

private:
	SDL_Window*		gWindow;
	SDL_Renderer*	gRenderer;
	TTF_Font*		gFont;
	GameState*		currentState;
	SceneType		nextSceneType;
	SDL_Event		event;
	bool			quit;
};

#endif // !SCENE_MANAGER_H
