#ifndef PADDLE_H
#define PADDLE_H
#include "gameBase.h"
#include "loadTexture.h"
class Paddle
{
public:

	Paddle();
	Paddle(float x, float y);
	~Paddle() = default;
	void PaddleMovement1(SDL_Event event, float deltaTime);
	void PaddleMovement2(SDL_Event event, float deltaTime);
	void drawPaddle(SDL_Renderer* renderer);
private:
	int paddleDirectionY;
	float paddleVelocity = 20.0;
	SDL_Rect paddlePosition;
};

#endif // !PADDLE_H
