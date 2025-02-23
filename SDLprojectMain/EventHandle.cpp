#include "EventHandle.h"

enum Buttons
{
	LEFT_PADDLE_UP,
	LEFT_PADDLE_DOWN,
	RIGHT_PADDLE_UP,
	RIGHT_PADDLE_DOWN,
	TOTAL_PADDLE = 4,
};

bool ButtonsInput[TOTAL_PADDLE];

Game::Game()
{
	gWindow = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, "Game");
	gRenderer = createRenderer(gWindow);
	paddle1 = Paddle(50, SCREEN_HEIGHT / 2);
	paddle2 = Paddle(SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2);
	ball = Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	deltaTime = (SDL_GetTicks() - tickcounts) / 1000.0f;
	tickcounts = SDL_GetTicks();
}

void Game::GetInput()
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			ButtonsInput[LEFT_PADDLE_UP] = true;
			break;
		case SDLK_s:
			ButtonsInput[LEFT_PADDLE_DOWN] = true;
			break;
		case SDLK_UP:
			ButtonsInput[RIGHT_PADDLE_UP] = true;
			break;
		case SDLK_DOWN:
			ButtonsInput[RIGHT_PADDLE_DOWN] = true;
			break;
		}
	}

	if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			ButtonsInput[LEFT_PADDLE_UP] = false;
			break;
		case SDLK_s:
			ButtonsInput[LEFT_PADDLE_DOWN] = false;
			break;
		case SDLK_UP:
			ButtonsInput[RIGHT_PADDLE_UP] = false;
			break;
		case SDLK_DOWN:
			ButtonsInput[RIGHT_PADDLE_DOWN] = false;
			break;
		}
	}
}

void Game::HandleInput()
{
	if (ButtonsInput[LEFT_PADDLE_UP] == false)
	{
		paddle1.paddleDirectionY = 0;
	}

	if (ButtonsInput[LEFT_PADDLE_DOWN] == false)
	{
		paddle1.paddleDirectionY = 0;
	}

	if (ButtonsInput[RIGHT_PADDLE_UP] == false)
	{
		paddle2.paddleDirectionY = 0;
	}

	if (ButtonsInput[RIGHT_PADDLE_DOWN] == false)
	{
		paddle2.paddleDirectionY = 0;
	}

	if (ButtonsInput[LEFT_PADDLE_UP] == true)
	{
		paddle1.paddleDirectionY = -1;
	}

	if (ButtonsInput[LEFT_PADDLE_DOWN] == true)
	{
		paddle1.paddleDirectionY = 1;
	}

	if (ButtonsInput[RIGHT_PADDLE_UP] == true)
	{
		paddle2.paddleDirectionY = -1;
	}

	if (ButtonsInput[RIGHT_PADDLE_DOWN] == true)
	{
		paddle2.paddleDirectionY = 1;
	}
}

void Game::render()
{
	SDL_RenderClear(gRenderer);

	paddle1.drawPaddle(gRenderer);

	paddle2.drawPaddle(gRenderer);

	ball.drawBall(gRenderer);

	/*SDL_RenderCopy(gRenderer, gTexturePaddle, NULL, NULL);*/

	SDL_RenderPresent(gRenderer);
}

bool Game::Collision(Ball ball, Paddle paddle)
{

	float UpperLeftBallCorner = ball.BallPosition.x;
	float UpperRightBallCorner = ball.BallPosition.x + ball.BallPosition.w;
	float LowerLeftBallCorner = ball.BallPosition.y;
	float LowerRightBallCorner = ball.BallPosition.y + ball.BallPosition.h;

	float UpperLeftPaddleCorner = paddle.paddlePosition.x;
	float UpperRightPaddleCorner = paddle.paddlePosition.x + paddle.paddlePosition.w;
	float LowerLeftPaddleCorner = paddle.paddlePosition.y;
	float LowerRightPaddleCorner = paddle.paddlePosition.y + paddle.paddlePosition.h;

	if (UpperLeftBallCorner >= UpperRightPaddleCorner)
	{
		return false;
	}

	if (UpperRightBallCorner <= UpperLeftPaddleCorner)
	{
		return false;
	}

	if (LowerLeftBallCorner >= LowerRightPaddleCorner)
	{
		return false;
	}

	if (LowerRightBallCorner <= LowerLeftPaddleCorner)
	{
		return false;
	}
	
	return true;
}


void Game::HandleCollision()
{
	if (Collision(ball, paddle1) == true || Collision(ball, paddle2) == true)
	{
		ball.BallVelocityX = -ball.BallVelocityX;
	}
}

void Game::gameLoop()
{
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			GetInput();
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		// handle input

		HandleInput();

		//paddle update

		paddle1.UpdatePaddlePosition(deltaTime);
		paddle2.UpdatePaddlePosition(deltaTime);

		//ball update

		ball.UpdateBallPosition(deltaTime);

		//handle collision with paddle

		HandleCollision();

		//score keeping for 2 players



		//scene manager for different menu screens



		// render game objects
		render();
	}
	quitSDL(gWindow, gRenderer);
}
