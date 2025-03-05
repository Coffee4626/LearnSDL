#include "Collision.h"

bool Collision::CheckCollision(Ball &ball, Paddle &paddle)
{
	float BallLeftSide = ball.BallPosition.x;
	float BallRightSide = ball.BallPosition.x + ball.BallPosition.w;
	float BallTopSide = ball.BallPosition.y;
	float BallBottomSide = ball.BallPosition.y + ball.BallPosition.h;

	float PaddleLeftSide = paddle.paddlePosition.x;
	float PaddleRightSide = paddle.paddlePosition.x + paddle.paddlePosition.w;
	float PaddleTopSide = paddle.paddlePosition.y;
	float PaddleBottomSide = paddle.paddlePosition.y + paddle.paddlePosition.h;

	if (BallLeftSide >= PaddleRightSide)
	{
		return false;
	}

	if (BallRightSide <= PaddleLeftSide)
	{
		return false;
	}

	if (BallTopSide >= PaddleBottomSide)
	{
		return false;
	}

	if (BallBottomSide <= PaddleTopSide)
	{
		return false;
	}
	return true;
}


void HandleCollision(Ball& ball, Paddle& paddle)
{
	float BallLeftSide = ball.BallPosition.x;
	float BallRightSide = ball.BallPosition.x + ball.BallPosition.w;
	float BallTopSide = ball.BallPosition.y;
	float BallBottomSide = ball.BallPosition.y + ball.BallPosition.h;

	float PaddleLeftSide = paddle.paddlePosition.x;
	float PaddleRightSide = paddle.paddlePosition.x + paddle.paddlePosition.w;
	float PaddleTopSide = paddle.paddlePosition.y;
	float PaddleBottomSide = paddle.paddlePosition.y + paddle.paddlePosition.h;


}