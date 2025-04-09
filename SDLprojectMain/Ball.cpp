#include "Ball.h"
using namespace pong;
Ball::Ball()
{
	BallPosition.x = 0;
	BallPosition.y = 0;
	BallPosition.w = 0;
	BallPosition.h = 0;
	InitialBallVelocityX = 0;
	InitialBallVelocityY = 0;
	BallVelocityX = InitialBallVelocityX;
	BallVelocityY = InitialBallVelocityY;
}

Ball::Ball(float x, float y)
{
	InitialBallVelocityX = 1.0f;
	InitialBallVelocityY = 0.5f;
	BallVelocityX = InitialBallVelocityX;
	BallVelocityY = InitialBallVelocityY;
	BallPosition.x = x;
	BallPosition.y = y;
	BallPosition.w = 15;
	BallPosition.h = 15;
}

void Ball::UpdateBallPosition(float &deltaTime)
{
	BallPosition.x = BallPosition.x + BallVelocityX * (deltaTime / 2);
	BallPosition.y = BallPosition.y + BallVelocityY * (deltaTime / 2);
	std::cout << BallVelocityY << std::endl;
}

void Ball::drawBall(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &BallPosition);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}



