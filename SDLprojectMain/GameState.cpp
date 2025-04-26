#include "GameState.h"
#include "StateManager.h"
using namespace pong;

void GameState::SetStateManager(GameStateManager* manager)
{
	mStateManager = manager;
}

void GameState::RequestChangeScene(SceneType newScene)
{
	if (mStateManager)
	{
		mStateManager->ChangeState(newScene);
	}
}
