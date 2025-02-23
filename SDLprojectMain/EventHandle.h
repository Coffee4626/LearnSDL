#ifndef EVENT_HANDLE
#define EVENT_HANDLE

#include "gameBase.h"
#include "Paddle.h"
#include "loadMedia.h"
#include "loadTexture.h"
#include "Ball.h"

class Game
{
public:
	Game();
	~Game() = default;
	void gameLoop();
	void render();
	void GetInput();
	void HandleInput();
	bool Collision(Ball ball, Paddle paddle);
	void HandleCollision();
private:
	Uint32 tickcounts;
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	Paddle paddle1;
	Paddle paddle2;
	Ball ball;
	SDL_Event event;
	float deltaTime;
	bool quit = false;
};

#endif // !EVENT_HANDLE
