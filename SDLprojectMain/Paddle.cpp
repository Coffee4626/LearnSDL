#include "Paddle.h"

Paddle::Paddle()
{
	paddleVelocity = 20.0f;
	paddleDirection = 0;
	paddlePosition.x = 0;
	paddlePosition.y = 0;
	paddlePosition.w = 25;
	paddlePosition.h = 75;
}

Paddle::Paddle(float x, float y)
{
	paddleVelocity = 20.0f;
	paddleDirection = 0;
	paddlePosition.x = static_cast<int>(x);
	paddlePosition.y = static_cast<int>(y);
	paddlePosition.w = 25;
	paddlePosition.h = 75;
}
void Paddle::paddleMovement(SDL_Event event, float deltaTime)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_UP:
				paddleDirection = -1;
				break;
			case SDLK_DOWN:
				paddleDirection = 1;
				break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		paddleDirection = 0;
	}
	if (paddlePosition.y + paddlePosition.h > SCREEN_HEIGHT)
	{
		paddlePosition.y = SCREEN_HEIGHT - paddlePosition.h - 10;
	}
	else if (paddlePosition.y - paddlePosition.h / 5 < 0)
	{
		paddlePosition.y = 0 + paddlePosition.h / 5;
	}
	else
	{
		paddlePosition.y += static_cast<float>(paddleDirection) * paddleVelocity * deltaTime;
	}
}



void Paddle::drawPaddle(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &paddlePosition);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}