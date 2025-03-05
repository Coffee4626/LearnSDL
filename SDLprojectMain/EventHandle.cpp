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

Game::Contact Game::Collision(Ball ball, Paddle paddle)
{
	float BallLeftSide = ball.BallPosition.x;
	float BallRightSide = ball.BallPosition.x + ball.BallPosition.w;
	float BallTopSide = ball.BallPosition.y;
	float BallBottomSide = ball.BallPosition.y + ball.BallPosition.h;

	float PaddleLeftSide = paddle.paddlePosition.x;
	float PaddleRightSide = paddle.paddlePosition.x + paddle.paddlePosition.w;
	float PaddleTopSide = paddle.paddlePosition.y;
	float PaddleBottomSide = paddle.paddlePosition.y + paddle.paddlePosition.h;

	float PaddleHeight = paddle.paddlePosition.y + paddle.paddlePosition.h;

	Contact contact = {};

	if (BallLeftSide >= PaddleRightSide)
	{
		return contact;
	}

	if (BallRightSide <= PaddleLeftSide)
	{
		return contact;
	}

	if (BallTopSide >= PaddleBottomSide)
	{
		return contact;
	}

	if (BallBottomSide <= PaddleTopSide)
	{
		return contact;
	}

	float paddleRangeUpper = PaddleBottomSide - (2.0f * PaddleHeight / 3.0f);
	float paddleRangeMiddle = PaddleBottomSide - (PaddleHeight / 3.0f);

	if (ball.BallVelocityX < 0)
	{
		// Left paddle
		contact.PenetrationDepth = PaddleRightSide - BallLeftSide;
	}
	else if (ball.BallVelocityY > 0)
	{
		// Right paddle
		contact.PenetrationDepth = PaddleLeftSide - BallRightSide;
	}

	if ((BallBottomSide > PaddleTopSide) && (BallBottomSide < paddleRangeUpper))
	{
		contact.ContactPoint = CollisionPoint::Top;
	}
	else if ((BallBottomSide > paddleRangeUpper) && (BallBottomSide < paddleRangeMiddle))
	{
		contact.ContactPoint = CollisionPoint::Middle;
	}
	else
	{
		contact.ContactPoint = CollisionPoint::Bottom;
	}
	return contact;
}

void Game::HandleCollision()
{
	Contact contact1 = Collision(ball, paddle1);
	Contact contact2 = Collision(ball, paddle2);

	if (contact1.ContactPoint != CollisionPoint::None)
	{
		ball.BallPosition.x += contact1.PenetrationDepth;
		ball.BallVelocityX = -ball.BallVelocityX;
		if (contact1.ContactPoint == CollisionPoint::Top)
		{
			ball.BallVelocityY = -1.2f * ball.BallVelocityY;
		}
		else if (contact1.ContactPoint == CollisionPoint::Bottom)
		{
			ball.BallVelocityY = 1.2f * ball.BallVelocityY;
		}
	}

	if (contact2.ContactPoint != CollisionPoint::None)
	{
		ball.BallPosition.x += contact2.PenetrationDepth;
		ball.BallVelocityX = -ball.BallVelocityX;
		if (contact2.ContactPoint == CollisionPoint::Top)
		{
			ball.BallVelocityY = -1.2f * ball.BallVelocityY;
		}
		else if (contact2.ContactPoint == CollisionPoint::Bottom)
		{
			ball.BallVelocityY = 1.2f * ball.BallVelocityY;
		}
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
