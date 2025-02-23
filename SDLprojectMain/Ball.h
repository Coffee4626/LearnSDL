#ifndef BALL_H
#define BALL_H

#include "gameBase.h"

class Ball
{

public:

	Ball();
	Ball(float x, float y);
	~Ball() = default;
	void UpdateBallPosition(float deltaTime);
	void drawBall(SDL_Renderer* renderer);
	void ResetBallVelocity();

	float InitialBallVelocityX;
	float InitialBallVelocityY;
	float BallVelocityX;
	float BallVelocityY;
	float acceleration;
	SDL_Rect BallPosition;

};

//ball logic

//bounce at panel

//bounce at wall

// bounce logic == geometry logic



#endif //!BALL_H

