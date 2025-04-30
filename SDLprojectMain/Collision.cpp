#include "Collision.h"

using namespace pong;

Collision::Contact Collision::CheckCollision(Ball& ball, Paddle& paddle)
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
		contact.PenetrationDepth = PaddleRightSide - BallLeftSide;
	}
	else if (ball.BallVelocityX > 0)
	{
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

Collision::Contact Collision::CheckCollisionWithWall(Ball& ball)
{
	float BallLeftSide = ball.BallPosition.x;
	float BallRightSide = ball.BallPosition.x + ball.BallPosition.w;
	float BallTopSide = ball.BallPosition.y;
	float BallBottomSide = ball.BallPosition.y + ball.BallPosition.h;

	Contact contact{};
	if (BallLeftSide <= 0.0f)
	{
		contact.ContactPoint = Collision::LeftWall;
	}
	else if (BallRightSide >= SCREEN_WIDTH)
	{
		contact.ContactPoint = Collision::RightWall;
	}
	else if (BallTopSide < 0.0f)
	{
		contact.ContactPoint = Collision::Top;
		contact.PenetrationDepth = -BallTopSide;
	}
	else if (BallBottomSide > SCREEN_HEIGHT)
	{
		contact.ContactPoint = Collision::Bottom;
		contact.PenetrationDepth = SCREEN_HEIGHT - BallBottomSide;
	}
	return contact;
}

void Collision::HandleCollision(Ball& ball, Paddle& paddle1, Paddle& paddle2)
{
	Contact contact1 = CheckCollision(ball, paddle1);
	Contact contact2 = CheckCollision(ball, paddle2);
	Contact contact3 = CheckCollisionWithWall(ball);

	if (contact1.ContactPoint != CollisionPoint::None)
	{
		ball.BallPosition.x += contact1.PenetrationDepth;
		ball.BallVelocityX = -1.05f * ball.BallVelocityX;
		if (contact1.ContactPoint == CollisionPoint::Top)
		{
			ball.BallVelocityY = -0.75f * 2;
		}
		else if (contact1.ContactPoint == CollisionPoint::UpperMiddle)
		{
			ball.BallVelocityY = -0.75f * 1;
		}
		else if (contact1.ContactPoint == CollisionPoint::LowerMiddle)
		{
			ball.BallVelocityY = 0.75f * 1;
		}
		else if (contact1.ContactPoint == CollisionPoint::Bottom)
		{
			ball.BallVelocityY = 0.75f * 2;
		}
	}
	if (contact2.ContactPoint != CollisionPoint::None)
	{
		ball.BallPosition.x += contact2.PenetrationDepth;
		ball.BallVelocityX = -1.05 * ball.BallVelocityX;

		if (contact2.ContactPoint == CollisionPoint::Top)
		{
			ball.BallVelocityY = -0.75 * 2;
		}
		else if (contact2.ContactPoint == CollisionPoint::UpperMiddle)
		{
			ball.BallVelocityY = -0.75f * 1;
		}
		else if (contact2.ContactPoint == CollisionPoint::LowerMiddle)
		{
			ball.BallVelocityY = 0.75f * 1;
		}
		else if (contact2.ContactPoint == CollisionPoint::Bottom)
		{
			ball.BallVelocityY = 0.75f * 2;
		}
	}
	if (contact3.ContactPoint == Collision::Top || contact3.ContactPoint == Collision::Bottom)
	{
		ball.BallPosition.y += contact3.PenetrationDepth;
		ball.BallVelocityY = -ball.BallVelocityY;
	}
	else if (contact3.ContactPoint == Collision::LeftWall)
	{
		//Reset ball position and velocity
		ball.BallPosition.x = SCREEN_WIDTH / 2;
		ball.BallPosition.y = SCREEN_HEIGHT / 2;
		ball.BallVelocityX = -ball.InitialBallVelocityX;
		ball.BallVelocityY = ball.InitialBallVelocityY;
	}
	else if (contact3.ContactPoint == Collision::RightWall)
	{
		//Reset ball position and velocity
		ball.BallPosition.x = SCREEN_WIDTH / 2;
		ball.BallPosition.y = SCREEN_HEIGHT / 2;
		ball.BallVelocityX = ball.InitialBallVelocityX;
		ball.BallVelocityY = ball.InitialBallVelocityY;
	}
}