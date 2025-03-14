#ifndef EVENT_HANDLE
#define EVENT_HANDLE

#include "GameBase.h"
#include "GameUtils.h"
#include "Collision.h"
#include "Paddle.h"
#include "Ball.h"

class Game
{
public:
	Game();
	~Game() = default;
	void gameLoop();
	void InitObject();
	void InitGame();
	void GetInput();
	void HandleInput();
	void UpdateObjects();
	void render();
	void close();
private:
	Uint32 tickcounts;
	TTF_Font* scoreFont;
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	LoadTexture player1score;
	int p1score;
	LoadTexture player2score;
	int p2score;
	LoadTexture scoreTexture;
	Paddle* paddle1;
	Paddle* paddle2;
	Ball* ball;
	SDL_Event event;
	float deltaTime;
	bool quit = false;
};

#endif // !EVENT_HANDLE
