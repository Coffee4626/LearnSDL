#include "Paddle.h"
using namespace pong;
Paddle::Paddle()
{
	paddleVelocity = 0.0f;
	paddleDirectionY = 0;
	paddlePosition.x = 0;
	paddlePosition.y = 0;
	paddlePosition.w = 0;
	paddlePosition.h = 0;
}

Paddle::Paddle(float x, float y)
{
	paddleVelocity = 1.5f;
	paddleDirectionY = 0;
	paddlePosition.x = static_cast<float>(x);
	paddlePosition.y = static_cast<float>(y);
	paddlePosition.w = 5;
	paddlePosition.h = 100;
}

void Paddle::UpdatePaddlePosition(float &deltaTime)
{
	if (paddlePosition.y + paddlePosition.h >= SCREEN_HEIGHT)
	{
		paddlePosition.y = SCREEN_HEIGHT - paddlePosition.h - 3;
	}
	else if (paddlePosition.y <= 0)
	{
		paddlePosition.y = 3;
	}
	else paddlePosition.y += static_cast<float>(paddleDirectionY) * paddleVelocity * deltaTime;
}

void Paddle::drawPaddle(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &paddlePosition);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
