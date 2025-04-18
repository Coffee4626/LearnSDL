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
	ball(nullptr),
	mIsPaused(false)
{
	
}

void Court::enter(SDL_Renderer* renderer, TTF_Font* font)
{
	this->mRenderer = renderer;
	this->mFont = font;
	paddle1 = new Paddle(50, SCREEN_HEIGHT / 2);
	paddle2 = new Paddle(SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2);
	ball = new Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mGame.getPlayerScores()[PlayerIndex::first] = 0;
	mGame.getPlayerScores()[PlayerIndex::second] = 0;
	LoadMedia();
}

void Court::LoadMedia()
{
	SDL_Color color = { 0x00, 0x00, 0x00, 0xFF };

	player1score.LoadFromRenderedText(std::to_string(mGame.getPlayerScores()[PlayerIndex::first]), mFont, color, mRenderer);

	player2score.LoadFromRenderedText(std::to_string(mGame.getPlayerScores()[PlayerIndex::second]), mFont, color, mRenderer);
	
	mBackgroundTexture.LoadFromFile("Assets/Pong court.png", mRenderer);

	mSpriteSheet.LoadFromFile("Assets/sprites.png", mRenderer);

	mDefaultBackground.LoadFromFile("Assets/Background.png", mRenderer);
	mDefaultBackground.SetAlpha(150);

	//Left paddle sprite
	mSpriteClips[0].x = 20;
	mSpriteClips[0].y = 20;
	mSpriteClips[0].w = 10;
	mSpriteClips[0].h = 130;
	//Right paddle sprite
	mSpriteClips[1].x = 70;
	mSpriteClips[1].y = 20;
	mSpriteClips[1].w = 10;
	mSpriteClips[1].h = 130;
	//Ball sprite
	mSpriteClips[2].x = 112;
	mSpriteClips[2].y = 12;
	mSpriteClips[2].w = 25;
	mSpriteClips[2].h = 25;
}

void Court::handleEvent(SDL_Event& event)
{
	//Getting inputs
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
		case SDLK_ESCAPE:
			if (mIsPaused == false) mIsPaused = true;
			else mIsPaused = false;
		}
	}
	//Handle when players stop holding keys
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
	//Paddles stationary when no inputs
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
	//Paddle moving based on input
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
	//Freeing textures
	player1score.Free();
	player2score.Free();
	mBackgroundTexture.Free();
	mSpriteSheet.Free();
	paddle1 = NULL;
	paddle2 = NULL;
	ball = NULL;
	delete ball;
	delete paddle2;
	delete paddle1;
}

void Court::updatePlayerScore()
{
	SDL_Color color = { 0x00, 0x00, 0x00, 0xFF };
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
	if (!mIsPaused)
	{
		collision.HandleCollision(*ball, *paddle1, *paddle2);
		updateGameObjects(deltaTime);
	}
}

void Court::render()
{
	//Render play court
	mBackgroundTexture.renderTexture(mRenderer, 0, 0);
	//Render players score
	player1score.renderTexture(mRenderer, SCREEN_WIDTH / 4, 20);
	player2score.renderTexture(mRenderer, 3 * SCREEN_WIDTH / 4, 20);
	//Render player paddles
	paddle1->RenderPaddle(&mSpriteClips[0], mRenderer, mSpriteSheet);
	paddle2->RenderPaddle(&mSpriteClips[1], mRenderer, mSpriteSheet);
	//Render ball
	ball->RenderBall(&mSpriteClips[2], mRenderer, mSpriteSheet);
	if (mIsPaused == true)
	{
		mDefaultBackground.renderTexture(mRenderer, 0, 0);
	}
}
