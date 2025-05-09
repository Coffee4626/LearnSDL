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
	BallPosition.w = 30;
	BallPosition.h = 30;
}

void Ball::UpdateBallPosition(float &deltaTime)
{
	BallPosition.x = BallPosition.x + BallVelocityX * (deltaTime / 2);
	BallPosition.y = BallPosition.y + BallVelocityY * (deltaTime / 2);
}

void Ball::RenderBall(SDL_Rect* currentClip, SDL_Renderer* renderer, LoadTexture mBallTexture)
{
	mBallTexture.renderTexture(renderer, BallPosition.x, BallPosition.y, currentClip);
}

int Ball::GetBallX()
{
	return BallPosition.x;
}

int Ball::GetBallY()
{
	return BallPosition.y;
}

//void Ball::ResetBall()
//{
//	BallPosition.x = SCREEN_WIDTH / 2;
//	BallPosition.y = SCREEN_HEIGHT / 2;
//	BallVelocityX = InitialBallVelocityX;
//	BallVelocityY = InitialBallVelocityY;
//}


