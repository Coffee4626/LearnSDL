#include "Ball.h"

Ball::Ball()
{
	BallPosition.x = 0;
	BallPosition.y = 0;
	BallPosition.w = 0;
	BallPosition.h = 0;
	BallVelocity = 0;
	acceleration = 0;
}

Ball::Ball(float x, float y)
{
	BallVelocity = 30.0f;
	BallPosition.x = x;
	BallPosition.y = y;
	BallPosition.w = 10;
	BallPosition.h = 10;
	acceleration = 0.0001;
}


void Ball::UpdateBallPosition(float deltaTime)
{
	BallPosition.x = BallPosition.x + BallVelocity * deltaTime + 1 / 2 * acceleration * deltaTime * deltaTime;
	BallPosition.y = BallPosition.y + BallVelocity * deltaTime + 1 / 2 * acceleration * deltaTime * deltaTime;

	//Ball collision with border

	if (BallPosition.x >= SCREEN_WIDTH || BallPosition.x <= 0)
	{
		BallPosition.x = SCREEN_WIDTH / 2;
	}
	if (BallPosition.y >= SCREEN_HEIGHT || BallPosition.y <= 0)
	{
		BallVelocity = -BallVelocity;
		BallPosition.y = BallPosition.y - SCREEN_HEIGHT;
	}
}

void Ball::drawBall(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &BallPosition);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}



