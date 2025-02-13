#include "Paddle.h"

Paddle::Paddle()
{
	paddleVelocity = 0;
	paddleDirectionX = 0;
	paddleDirectionY = 0;
	paddlePosition.x = 0;
	paddlePosition.y = 0;
	paddlePosition.w = 0;
	paddlePosition.h = 0;
}

Paddle::Paddle(float x, float y)
{
	paddleVelocity = 20.0f;
	paddleDirectionX = 0;
	paddleDirectionY = 0;
	paddlePosition.x = static_cast<int>(x);
	paddlePosition.y = static_cast<int>(y);
	paddlePosition.w = 75;
	paddlePosition.h = 25;
}
void Paddle::paddleMovement(SDL_Event event, float deltaTime)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_LEFT:
				paddleDirectionX = -1;
				break;
			case SDLK_RIGHT:
				paddleDirectionX = 1;
				break;
			case SDLK_UP:
				paddleDirectionY = -1;
				break;
			case SDLK_DOWN:
				paddleDirectionY = 1;
				break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		paddleDirectionX = 0;
		paddleDirectionY = 0;
	}
	// handling collision with window border
	if (paddlePosition.x + paddlePosition.w > SCREEN_WIDTH)
	{
		paddlePosition.x = SCREEN_WIDTH - paddlePosition.w - 10;
	}
	else if (paddlePosition.x - paddlePosition.w / 5 < 0)
	{
		paddlePosition.x = 0 + paddlePosition.w / 5;
	}
	else
	{
		paddlePosition.x += static_cast<float>(paddleDirectionX) * paddleVelocity * deltaTime;
		paddlePosition.y += static_cast<float>(paddleDirectionY) * paddleVelocity * deltaTime;
	}
}



void Paddle::drawPaddle(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &paddlePosition);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}