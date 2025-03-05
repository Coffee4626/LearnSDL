#ifndef COLLISION_H
#define COLLISION_H

#include "Ball.h"
#include "Paddle.h"


class Collision
{
public:
	bool CheckCollision(Ball &ball, Paddle &paddle);

};

#endif // !COLLISION_H
