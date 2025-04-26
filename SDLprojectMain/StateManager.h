#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <map>
#include <memory>
#include "GameState.h"

namespace pong
{
	class GameStateManager
	{
	public:
		void ChangeState(SceneType newScene);
		SceneType GetCurrentState() const;
		void LoadState(SceneType newScene, std::shared_ptr<GameState> state);
		void HandleEvent(SDL_Event& event);
		void Update(float deltaTime);
		void Render();
	private:
		SceneType mCurrentScene = SceneType::TITLE_SCREEN;
		std::map<SceneType, std::shared_ptr<GameState>> mLoadedStates;
	};
}
#endif // !STATE_MANAGER_H
