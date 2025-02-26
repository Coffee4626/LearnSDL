#include "Paddle.h"

Paddle::Paddle()
{
	paddleVelocity = 20.0f;
	paddleDirectionY = 0;
	paddlePosition.x = 0;
	paddlePosition.y = 0;
	paddlePosition.w = 0;
	paddlePosition.h = 0;
}

Paddle::Paddle(float x, float y)
{
	paddleVelocity = 15.0f;
	paddleDirectionY = 0;
	paddlePosition.x = static_cast<int>(x);
	paddlePosition.y = static_cast<int>(y);
	paddlePosition.w = 5;
	paddlePosition.h = 100;
}
void Paddle::PaddleMovement1(SDL_Event event, float deltaTime)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
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
		paddleDirectionY = 0;
	}
	if (paddlePosition.y + paddlePosition.h >= SCREEN_HEIGHT)
	{
		paddlePosition.y = SCREEN_HEIGHT - paddlePosition.h;
		//std::cout << "YES" << std::endl;
	}
	else if (paddlePosition.y - paddlePosition.h / 2 < 0)
	{
		paddlePosition.y += 0 + paddlePosition.h / 2;
	}
	else
	{
		paddlePosition.y += static_cast<float>(paddleDirectionY) * paddleVelocity * deltaTime;
	}
}

void Paddle::PaddleMovement2(SDL_Event event, float deltaTime)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_w:
				paddleDirectionY = -1;
				break;
			case SDLK_s:
				paddleDirectionY = 1;
				break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		paddleDirectionY = 0;
	}
	if (paddlePosition.y + paddlePosition.w / 2 >= SCREEN_HEIGHT)
	{
		paddlePosition.y += SCREEN_HEIGHT - paddlePosition.w / 2;
	}
	else if (paddlePosition.y - paddlePosition.w / 2 < 0)
	{
		paddlePosition.y += 0 + paddlePosition.w / 2;
	}
	else
	{
		paddlePosition.y += static_cast<float>(paddleDirectionY) * paddleVelocity * deltaTime;
	}
}

void Paddle::UpdatePaddlePosition(float deltaTime)
{
	if (paddlePosition.y + paddlePosition.h >= SCREEN_HEIGHT)
	{
		paddlePosition.y = SCREEN_HEIGHT - paddlePosition.h - 3;
		//std::cout << "YES" << std::endl;
	}
	else if (paddlePosition.y <= 0)
	{
		paddlePosition.y = 3;
	}
	else paddlePosition.y += paddleDirectionY * paddleVelocity * deltaTime;
}


void Paddle::drawPaddle(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &paddlePosition);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
