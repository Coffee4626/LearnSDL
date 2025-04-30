#ifndef COLLISION_H
#define COLLISION_H

#include "Ball.h"
#include "Paddle.h"

namespace pong
{
	class Collision
	{
	public:

		enum CollisionPoint
		{
			None,
			Top,
			UpperMiddle,
			LowerMiddle,
			Bottom,
			LeftWall,
			RightWall
		};

		struct Contact
		{
			float PenetrationDepth;
			CollisionPoint ContactPoint;
		};

		Contact		CheckCollision(Ball& ball, Paddle& paddle);
		Contact		CheckCollisionWithWall(Ball& ball);
		void		HandleCollision(Ball& ball, Paddle& paddle1, Paddle& paddle2);
	};
}

#endif // !COLLISION_H