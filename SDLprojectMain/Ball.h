#ifndef BALL_H
#define BALL_H

#include "GameBase.h"

namespace pong
{
	class Ball
	{

	public:

		Ball();
		Ball(float x, float y);
		~Ball() = default;
		void UpdateBallPosition(float &deltaTime);
		void RenderBall(SDL_Rect* currentClip, SDL_Renderer* renderer, LoadTexture mBallTexture);
		float InitialBallVelocityX;
		float InitialBallVelocityY;
		float BallVelocityX;
		float BallVelocityY;
		SDL_Rect BallPosition;

	};
}

#endif //!BALL_H

