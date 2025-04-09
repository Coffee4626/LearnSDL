#include "CourtScreen.h"

enum buttons
{
	left_paddle_up,
	left_paddle_down,
	right_paddle_up,
	right_paddle_down,
	total_paddle = 4,
};

bool buttonsinput[total_paddle];


Court::Court()
{
	paddle1 = NULL;
	paddle2 = NULL;
	ball = NULL;
	p1score = 0;
	p2score = 0;
}

void Court::enter(SDL_Renderer* renderer, TTF_Font* font)
{
	SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };
	if (!player1score.LoadFromRenderedText(std::to_string(p1score), font, color, renderer))
	{
		std::cout << "Failed to load instructions for p1" << std::endl;
		return;
	}
	if (!player2score.LoadFromRenderedText(std::to_string(p2score), font, color, renderer))
	{
		std::cout << "Failed to load instructions for p2" << std::endl;
		return;
	}
	paddle1 = new Paddle(50, SCREEN_HEIGHT / 2);
	paddle2 = new Paddle(SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2);
	ball = new Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	deltaTime = (SDL_GetTicks() - tickcounts) / 1000.0f;
	tickcounts = SDL_GetTicks();
	this->mRenderer = renderer;
	this->playerScore = font;
}

void Court::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			buttonsinput[left_paddle_up] = true;
			break;
		case SDLK_s:
			buttonsinput[left_paddle_down] = true;
			break;
		case SDLK_UP:
			buttonsinput[right_paddle_up] = true;
			break;
		case SDLK_DOWN:
			buttonsinput[right_paddle_down] = true;
			break;
		}
	}

	if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			buttonsinput[left_paddle_up] = false;
			break;
		case SDLK_s:
			buttonsinput[left_paddle_down] = false;
			break;
		case SDLK_UP:
			buttonsinput[right_paddle_up] = false;
			break;
		case SDLK_DOWN:
			buttonsinput[right_paddle_down] = false;
			break;
		}
	}
}

void Court::handleInput()
{
	if (buttonsinput[left_paddle_up] == false)
	{
		paddle1->paddleDirectionY = 0;
	}

	if (buttonsinput[left_paddle_down] == false)
	{
		paddle1->paddleDirectionY = 0;
	}

	if (buttonsinput[right_paddle_up] == false)
	{
		paddle2->paddleDirectionY = 0;
	}

	if (buttonsinput[right_paddle_down] == false)
	{
		paddle2->paddleDirectionY = 0;
	}

	if (buttonsinput[left_paddle_up] == true)
	{
		paddle1->paddleDirectionY = -1;
	}

	if (buttonsinput[left_paddle_down] == true)
	{
		paddle1->paddleDirectionY = 1;
	}

	if (buttonsinput[right_paddle_up] == true)
	{
		paddle2->paddleDirectionY = -1;
	}

	if (buttonsinput[right_paddle_down] == true)
	{
		paddle2->paddleDirectionY = 1;
	}
}

void Court::exit()
{
	player1score.Free();
	player2score.Free();
	paddle1 = NULL;
	paddle2 = NULL;
	ball = NULL;
	delete paddle1;
	delete paddle2;
	delete ball;
}

void Court::updatePlayerScore()
{
	SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };
	Collision::Contact contact = collision.CheckCollisionWithWall(*ball);
	if (contact.ContactPoint == Collision::LeftWall)
	{
		p2score++;
		player2score.LoadFromRenderedText(std::to_string(p2score), playerScore, color, mRenderer);
	}
	if (contact.ContactPoint == Collision::RightWall)
	{
		p1score++;
		player1score.LoadFromRenderedText(std::to_string(p1score), playerScore, color, mRenderer);
	}
}

void Court::updateGameObjects()
{
	paddle1->UpdatePaddlePosition(deltaTime);
	paddle2->UpdatePaddlePosition(deltaTime);
	ball->UpdateBallPosition(deltaTime);
	updatePlayerScore();
}

void Court::update()
{
	handleInput();
	collision.HandleCollision(*ball, *paddle1, *paddle2);
	updateGameObjects();
}

void Court::render()
{
	player1score.renderTexture(mRenderer, SCREEN_WIDTH / 4, 20);

	player2score.renderTexture(mRenderer, 3 * SCREEN_WIDTH / 4, 20);

	paddle1->drawPaddle(mRenderer);

	paddle2->drawPaddle(mRenderer);

	ball->drawBall(mRenderer);
}

bool Court::checkChangeState()
{
	if (p1score > 10)
	{
		p1win = true;
		return true;
	}
	if (p2score > 10)
	{
		p2win = true;
		return true;
	}
	return false;
}

SceneType Court::getNextScene()
{
	return SceneType::RESULT_SCREEN;
}