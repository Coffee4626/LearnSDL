#ifndef PADDLE_H
#define PADDLE_H
#include "GameBase.h"
namespace pong
{
	class Paddle
	{
	public:

		Paddle();
		Paddle(float x, float y);
		~Paddle() = default;
		void UpdatePaddlePosition(float &deltaTime);
		void RenderPaddle(SDL_Rect* currentClip, SDL_Renderer* renderer, LoadTexture mPaddleTexture);

		int paddleDirectionY;
		float paddleVelocity = 20.0;
		SDL_Rect paddlePosition;
	};
}

#endif // !PADDLE_H
