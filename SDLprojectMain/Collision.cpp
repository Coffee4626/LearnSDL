#include "Collision.h"


Collision::Contact Collision::CheckCollision(Ball ball, Paddle paddle)
{
	float BallLeftSide = ball.BallPosition.x;
	float BallRightSide = ball.BallPosition.x + ball.BallPosition.w;
	float BallTopSide = ball.BallPosition.y;
	float BallBottomSide = ball.BallPosition.y + ball.BallPosition.h;

	float PaddleLeftSide = paddle.paddlePosition.x;
	float PaddleRightSide = paddle.paddlePosition.x + paddle.paddlePosition.w;
	float PaddleTopSide = paddle.paddlePosition.y;
	float PaddleBottomSide = paddle.paddlePosition.y + paddle.paddlePosition.h;

	float PaddleHeight = paddle.paddlePosition.h;

	Contact contact = {};

	if (BallLeftSide >= PaddleRightSide)
	{
		return contact;
	}

	if (BallRightSide <= PaddleLeftSide)
	{
		return contact;
	}

	if (BallTopSide >= PaddleBottomSide)
	{
		return contact;
	}

	if (BallBottomSide <= PaddleTopSide)
	{
		return contact;
	}

	float PaddleRangeUpper = PaddleBottomSide - (3.0f * PaddleHeight / 4.0f);
	float PaddleRangeUpperMiddle = PaddleBottomSide - (1.0f * PaddleHeight / 2.0f);
	float PaddleRangeLowerMiddle = PaddleBottomSide - (1.0f * PaddleHeight / 4.0f);

	if (ball.BallVelocityX < 0)
	{
		// Left paddle
		contact.PenetrationDepth = PaddleRightSide - BallLeftSide;
	}
	else if (ball.BallVelocityX > 0)
	{
		// Right paddle
		contact.PenetrationDepth = PaddleLeftSide - BallRightSide;
	}

	if ((BallBottomSide > PaddleTopSide) && (BallBottomSide < PaddleRangeUpper))
	{
		contact.ContactPoint = CollisionPoint::Top;
	}
	else if ((BallBottomSide > PaddleRangeUpper) && (BallBottomSide < PaddleRangeUpperMiddle))
	{
		contact.ContactPoint = CollisionPoint::UpperMiddle;
	}
	else if ((BallBottomSide > PaddleRangeUpperMiddle) && (BallBottomSide < PaddleRangeLowerMiddle))
	{
		contact.ContactPoint = CollisionPoint::LowerMiddle;
	}
	else
	{
		contact.ContactPoint = CollisionPoint::Bottom;
	}

	return contact;
}

void Collision::HandleCollision(Ball &ball, Paddle &paddle1, Paddle &paddle2)
{
	Contact contact1 = CheckCollision(ball, paddle1);
	Contact contact2 = CheckCollision(ball, paddle2);

	if (contact1.ContactPoint != CollisionPoint::None)
	{
		ball.BallPosition.x += contact1.PenetrationDepth;
		ball.BallVelocityX = -1.25f * ball.BallVelocityX;

		if (contact1.ContactPoint == CollisionPoint::Top)
		{
			ball.BallVelocityY = -1.41f * ball.BallVelocityY;
		}
		else if (contact1.ContactPoint == CollisionPoint::UpperMiddle)
		{
			ball.BallVelocityY = -0.75f * 5;
		}
		else if (contact1.ContactPoint == CollisionPoint::LowerMiddle)
		{
			ball.BallVelocityY = 0.75f * 5;
		}
		else if (contact1.ContactPoint == CollisionPoint::Bottom)
		{
			ball.BallVelocityY = 1.41f * ball.BallVelocityY;
		}
	}

	if (contact2.ContactPoint != CollisionPoint::None)
	{
		ball.BallPosition.x += contact2.PenetrationDepth;
		ball.BallVelocityX = -ball.BallVelocityX;

		if (contact2.ContactPoint == CollisionPoint::Top)
		{
			ball.BallVelocityY = -1.41f * ball.BallVelocityY;
		}
		else if (contact2.ContactPoint == CollisionPoint::UpperMiddle)
		{
			ball.BallVelocityY = -0.75f * 5;
		}
		else if (contact2.ContactPoint == CollisionPoint::LowerMiddle)
		{
			ball.BallVelocityY = 0.75f * 5;
		}
		else if (contact2.ContactPoint == CollisionPoint::Bottom)
		{
			ball.BallVelocityY = 1.41f * ball.BallVelocityY;
		}
	}
}

