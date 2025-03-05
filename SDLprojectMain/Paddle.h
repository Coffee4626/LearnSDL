#ifndef PADDLE_H
#define PADDLE_H
#include "gameBase.h"
#include "loadTexture.h"
#include "Geometry.h"
class Paddle
{
public:

	Paddle();
	Paddle(float x, float y);
	~Paddle() = default;
	void UpdatePaddlePosition(float deltaTime);
	void drawPaddle(SDL_Renderer* renderer);

	int paddleDirectionY;
	float paddleVelocity = 20.0;
	SDL_Rect paddlePosition;
};

#endif // !PADDLE_H
