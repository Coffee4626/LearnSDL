#include "CourtScreen.h"
#include "ResultScreen.h"
#include "Game.h"

using namespace pong;

bool buttonsinput[total_paddle];

Court::Court(Game& game) : 
	mGame(game),
	mRenderer(nullptr),
	mFont(nullptr),
	paddle1(nullptr), 
	paddle2(nullptr), 
	ball(nullptr)
{

}

void Court::enter(SDL_Renderer* renderer, TTF_Font* font)
{
	this->mRenderer = renderer;
	this->mFont = font;
	SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };
	paddle1 = new Paddle(50, SCREEN_HEIGHT / 2);
	paddle2 = new Paddle(SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2);
	ball = new Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mGame.getPlayerScores()[PlayerIndex::first] = 0;
	mGame.getPlayerScores()[PlayerIndex::second] = 0;
	if (!player1score.LoadFromRenderedText(std::to_string(mGame.getPlayerScores()[PlayerIndex::first]), mFont, color, mRenderer))
	{
		std::cout << "Failed to load instructions for p1" << std::endl;
		return;
	}
	if (!player2score.LoadFromRenderedText(std::to_string(mGame.getPlayerScores()[PlayerIndex::second]), mFont, color, mRenderer))
	{
		std::cout << "Failed to load instructions for p2" << std::endl;
		return;
	}
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
	delete ball;
	delete paddle2;
	delete paddle1;
}

void Court::updatePlayerScore()
{
	SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };
	Collision::Contact contact = collision.CheckCollisionWithWall(*ball);
	auto& scores = mGame.getPlayerScores();
	if (contact.ContactPoint == Collision::RightWall)
	{
		scores[PlayerIndex::first]++;
		player1score.LoadFromRenderedText(std::to_string(scores[PlayerIndex::first]), mFont, color, mRenderer);
	}
	if (contact.ContactPoint == Collision::LeftWall)
	{
		scores[PlayerIndex::second]++;
		player2score.LoadFromRenderedText(std::to_string(scores[PlayerIndex::second]), mFont, color, mRenderer);
	}
	if (scores[PlayerIndex::first] > 2 || scores[PlayerIndex::second] > 2)
	{
		mGame.ChangeState(std::make_shared<End>(mGame));
	}
}

void Court::updateGameObjects(float &mTime)
{
	//Update paddle position based on time
	paddle1->UpdatePaddlePosition(mTime);
	paddle2->UpdatePaddlePosition(mTime);
	//Update ball position based on time
	ball->UpdateBallPosition(mTime);
	//Update player score
	updatePlayerScore();
}

void Court::update(float deltaTime)
{
	handleInput();
	collision.HandleCollision(*ball, *paddle1, *paddle2);
	updateGameObjects(deltaTime);
}

void Court::render()
{
	//Render players score
	player1score.renderTexture(mRenderer, SCREEN_WIDTH / 4, 20);
	player2score.renderTexture(mRenderer, 3 * SCREEN_WIDTH / 4, 20);
	//Render player paddles
	paddle1->drawPaddle(mRenderer);
	paddle2->drawPaddle(mRenderer);
	//Render ball
	ball->drawBall(mRenderer);
}
