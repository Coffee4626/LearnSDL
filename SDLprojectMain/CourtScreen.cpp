#include "CourtScreen.h"
#include "StateManager.h"
#include "Game.h"

using namespace pong;

bool buttonsinput[total_paddle];

Court::Court(Game& game, SDL_Renderer* renderer, TTF_Font* font) :
	mGame(game),
	mRenderer(renderer),
	mFont(font),
	paddle1(nullptr),
	paddle2(nullptr),
	ball(nullptr),
	mIsPaused(false),
	mSelectedMenuIndex(0)
{
	std::cout << "Court constructor called" << std::endl;
	LoadMedia();
}

Court::~Court()
{
	mBackgroundTexture.Free();
	mDefaultBackground.Free();
	mPausedText.Free();
	mSpriteSheet.Free();
	mBallHitPaddle.Free();
	mBallHitWall.Free();
	player1score.Free();
	player2score.Free();
	mResumeTextNormal.Free();
	mQuitTextNormal.Free();
	mResumeTextSelected.Free();
	mQuitTextSelected.Free();

	for (int i = 0; i < TOTAL_PARTICLES; i++)
	{
		delete particles[i];
	}

	std::cout << "Court destructor called" << std::endl;
}

void Court::enter()
{
	mIsPaused = false;
	paddle1 = new Paddle(50, SCREEN_HEIGHT / 2);
	paddle2 = new Paddle(SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2);
	ball = new Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mScore = mGame.GetMaxScore();
	mGame.getPlayerScores()[PlayerIndex::first] = 0;
	mGame.getPlayerScores()[PlayerIndex::second] = 0;

	for (int i = 0; i < TOTAL_PARTICLES; i++)
	{
		particles[i] = new Particle(ball->GetBallX(), ball->GetBallY(), &mParticleTexture, &mShimmerTexture);
	}

	SDL_Color black = { 0x00, 0x00, 0x00, 0xFF };
	player1score.LoadFromRenderedText(std::to_string(mGame.getPlayerScores()[PlayerIndex::first]), mFont, black, mRenderer);

	player2score.LoadFromRenderedText(std::to_string(mGame.getPlayerScores()[PlayerIndex::second]), mFont, black, mRenderer);

	std::cout << "Entered Court screen" << std::endl;
}

void Court::LoadMedia()
{
	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
	SDL_Color yellow = { 0xFF, 0xFF, 0x00, 0xFF };

	mPausedText.LoadFromRenderedText("Paused", mFont, white, mRenderer);
	LoadText(mResumeTextNormal, mResumeTextSelected, "Resume", white, yellow);
	LoadText(mQuitTextNormal, mQuitTextSelected, "Quit", white, yellow);

	//Load Particles
	mParticleTexture.LoadFromFile("Assets/red.bmp", mRenderer);
	mShimmerTexture.LoadFromFile("Assets/shimmer.bmp", mRenderer);

	//Load backgrounds
	mBackgroundTexture.LoadFromFile("Assets/Pong court.png", mRenderer);

	mSpriteSheet.LoadFromFile("Assets/sprites.png", mRenderer);

	mDefaultBackground.LoadFromFile("Assets/Background.png", mRenderer);
	mDefaultBackground.SetAlpha(150);

	mBallHitPaddle.LoadSound("Assets/BallHitPaddle.wav");
	mBallHitWall.LoadSound("Assets/BallHitWall.wav");

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


void Court::LoadText(LoadTexture& normal, LoadTexture& selected,
	const std::string& content, SDL_Color normalColor, SDL_Color selectedColor)
{
	normal.LoadFromRenderedText(content, mFont, normalColor, mRenderer);
	selected.LoadFromRenderedText(content, mFont, selectedColor, mRenderer);
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
			if (mIsPaused == false)
			{
				buttonsinput[right_paddle_up] = true;
			}
			else mSelectedMenuIndex = (mSelectedMenuIndex - 1 + CourtIndex::totalCourtMenu) % CourtIndex::totalCourtMenu;
			break;
		case SDLK_DOWN:
			if (mIsPaused == false)
			{
				buttonsinput[right_paddle_down] = true;
			}
			else mSelectedMenuIndex = (mSelectedMenuIndex + 1) % CourtIndex::totalCourtMenu;
			break;
		case SDLK_ESCAPE:
			if (mIsPaused == false) mIsPaused = true;
			else mIsPaused = false;
			break;
		case SDLK_RETURN:
			if (mIsPaused == true)
			{
				switch (mSelectedMenuIndex)
				{
				case CourtIndex::Court_Resume:
					mIsPaused = false;
					break;
				case CourtIndex::Court_Quit:
					std::cout << "Quit button selected" << std::endl;
					RequestChangeScene(SceneType::TITLE_SCREEN);
					break;
				}
			}
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
	paddle1 = NULL;
	paddle2 = NULL;
	ball = NULL;
	delete ball;
	delete paddle2;
	delete paddle1;
	std::cout << "Court screen exited" << std::endl;
}

void Court::updatePlayerScore()
{
	SDL_Color black = { 0x00, 0x00, 0x00, 0xFF };
	Collision::Contact contact = collision.CheckCollisionWithWall(*ball);
	auto& scores = mGame.getPlayerScores();
	if (contact.ContactPoint == Collision::RightWall)
	{
		scores[PlayerIndex::first]++;
		player1score.LoadFromRenderedText(std::to_string(scores[PlayerIndex::first]), mFont, black, mRenderer);
	}
	if (contact.ContactPoint == Collision::LeftWall)
	{
		scores[PlayerIndex::second]++;
		player2score.LoadFromRenderedText(std::to_string(scores[PlayerIndex::second]), mFont, black, mRenderer);
	}
	if (scores[PlayerIndex::first] > mScore || scores[PlayerIndex::second] > mScore)
	{
		RequestChangeScene(SceneType::RESULT_SCREEN);
	}
}



void Court::updateGameObjects(float& mTime)
{
	//Update paddle position based on time
	paddle1->UpdatePaddlePosition(mTime);
	paddle2->UpdatePaddlePosition(mTime);
	//Update ball position based on time
	ball->UpdateBallPosition(mTime);
	Collision::Contact contact1 = collision.CheckCollisionWithWall(*ball);
	Collision::Contact contact2 = collision.CheckCollision(*ball, *paddle1);
	Collision::Contact contact3 = collision.CheckCollision(*ball, *paddle2);
	if (contact1.ContactPoint == Collision::Top || contact1.ContactPoint == Collision::Bottom)
	{
		mBallHitWall.PlaySound(-1, 0, mGame.gSound.GetVolume());
	}
	if (contact2.ContactPoint != Collision::None || contact3.ContactPoint != Collision::None)
	{
		mBallHitPaddle.PlaySound(-1, 0, mGame.gSound.GetVolume());
	}
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

void Court::RenderParticles()
{
	for (int i = 0; i < TOTAL_PARTICLES; i++)
	{
		if (particles[i]->isDead())
		{
			delete particles[i];
			particles[i] = new Particle(ball->GetBallX(), ball->GetBallY(), &mParticleTexture, &mShimmerTexture);
		}
	}

	for (int i = 0; i < TOTAL_PARTICLES; i++)
	{
		particles[i]->Render(mRenderer);
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
	RenderParticles();
	if (mIsPaused == true)
	{
		//Display court menu
		RenderCourtMenu();
	}
}

void Court::RenderCourtMenu()
{
	int yOffSet = 50;
	mDefaultBackground.renderTexture(mRenderer, 0, 0);
	mPausedText.renderTexture(mRenderer,
		(SCREEN_WIDTH - mPausedText.getWidth()) / 2,
		(SCREEN_HEIGHT - mPausedText.getHeight()) / 2 - 50);
	if (mSelectedMenuIndex == CourtIndex::Court_Resume)
	{
		mResumeTextSelected.renderTexture(mRenderer,
			(SCREEN_WIDTH - mResumeTextSelected.getWidth()) / 2,
			(SCREEN_HEIGHT - mResumeTextSelected.getHeight()) / 2 + yOffSet);
	}
	else
	{
		mResumeTextNormal.renderTexture(mRenderer,
			(SCREEN_WIDTH - mResumeTextNormal.getWidth()) / 2,
			(SCREEN_HEIGHT - mResumeTextNormal.getHeight()) / 2 + yOffSet);
	}
	if (mSelectedMenuIndex == CourtIndex::Court_Quit)
	{
		mQuitTextSelected.renderTexture(mRenderer,
			(SCREEN_WIDTH - mQuitTextSelected.getWidth()) / 2,
			(SCREEN_HEIGHT - mQuitTextSelected.getHeight()) / 2 + yOffSet * 2);
	}
	else
	{
		mQuitTextNormal.renderTexture(mRenderer,
			(SCREEN_WIDTH - mQuitTextNormal.getWidth()) / 2,
			(SCREEN_HEIGHT - mQuitTextNormal.getHeight()) / 2 + yOffSet * 2);
	}
}