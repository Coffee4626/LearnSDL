#ifndef PADDLE_H
#define PADDLE_H
#include "gameBase.h"
class Paddle
{
public:
	Paddle();
	Paddle(float x, float y);
	~Paddle() = default;
	void paddleMovement(SDL_Event event, float deltaTime);
	void drawPaddle(SDL_Renderer* renderer);
private:
	int paddleDirection;
	float paddleVelocity = 20.0f;
	SDL_Rect paddlePosition;
};
#endif // !PADDLE_H
