#include "Ball.h"

Ball::Ball()
{
	BallPosition.x = 0;
	BallPosition.y = 0;
	BallPosition.w = 0;
	BallPosition.h = 0;
	InitialBallVelocityX = 0;
	InitialBallVelocityY = 0;
	acceleration = 0;
}

Ball::Ball(float x, float y)
{
	InitialBallVelocityX = 12.0f;
	InitialBallVelocityY = 5.0f;
	BallVelocityX = InitialBallVelocityX;
	BallVelocityY = InitialBallVelocityY;
	BallPosition.x = x;
	BallPosition.y = y;
	BallPosition.w = 15;
	BallPosition.h = 15;
	acceleration = 0.02f;
}

void Ball::ResetBallVelocity()
{
	BallVelocityX = InitialBallVelocityX;
	BallVelocityY = InitialBallVelocityY;
}


void Ball::UpdateBallPosition(float deltaTime)
{
	BallPosition.x = BallPosition.x + BallVelocityX * deltaTime;
	BallPosition.y = BallPosition.y + BallVelocityY * deltaTime;

	//Ball collision with border

	if (BallPosition.x >= SCREEN_WIDTH || BallPosition.x <= 0)
	{
		BallPosition.x = SCREEN_WIDTH / 2;
		BallPosition.y = SCREEN_HEIGHT / 2;
		ResetBallVelocity();
	}

	if (BallPosition.y >= SCREEN_HEIGHT || BallPosition.y <= 0)
	{
		BallVelocityY = -BallVelocityY;
	}

}

void Ball::drawBall(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &BallPosition);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}



