#include "StateManager.h"

using namespace pong;

void GameStateManager::LoadState(SceneType scene, std::shared_ptr<GameState> scenePtr)
{
	mLoadedStates[scene] = scenePtr;
	scenePtr->SetStateManager(this);
}

void GameStateManager::ChangeState(SceneType newScene)
{
	auto PreviousScene = mLoadedStates[mCurrentScene];
	if (PreviousScene)
	{
		PreviousScene->exit();
	}
	mCurrentScene = newScene;
	auto CurrentScene = mLoadedStates[mCurrentScene];
	if (CurrentScene)
	{
		CurrentScene->enter();
	}
}

SceneType GameStateManager::GetCurrentState() const
{
	return mCurrentScene;
}

void GameStateManager::HandleEvent(SDL_Event& event)
{
	auto CurrentScene = mLoadedStates[mCurrentScene];
	if (CurrentScene)
	{
		CurrentScene->handleEvent(event);
	}
}

void GameStateManager::Update(float deltaTime)
{
	auto CurrentScene = mLoadedStates[mCurrentScene];
	if (CurrentScene)
	{
		CurrentScene->update(deltaTime);
	}
}

void GameStateManager::Render()
{
	auto CurrentScene = mLoadedStates[mCurrentScene];
	if (CurrentScene)
	{
		CurrentScene->render();
	}
}