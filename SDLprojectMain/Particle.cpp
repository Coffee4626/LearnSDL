#include "Particle.h"

using namespace pong;

//Particle::Particle(float x, float y, int life, float angle, int speed, int size, SDL_Color color)
//{
//	this->mPosition.x = x;
//	this->mPosition.y = y;
//	this->mLifespan = life;
//
//	float rad = angle * (M_PI / 180.0f);
//	this->mVelocity.x = speed * cos(rad);
//	this->mVelocity.y = -speed * sin(rad);
//
//	this->color = { 0xFF, 0xFF, 0xFF, 0xFF };
//}
//
//
//void Particle::Update(float deltaTime)
//{
//	this->mLifespan -= static_cast<float>(deltaTime);
//	if (this->mLifespan > 0)
//	{
//		this->mPosition.x += this->mVelocity.x * deltaTime;
//		this->mPosition.y += this->mVelocity.y * deltaTime;
//	}
//}

Particle::Particle(int x, int y, LoadTexture* texture, LoadTexture* shimmer)
{
    mPosX = x - 5 + (rand() % 25);
    mPosY = y - 5 + (rand() % 25);

    mFrame = rand() % 5;
    
    this->mTexture = texture;
    this->mShimmer = shimmer;

}

void Particle::Render(SDL_Renderer* renderer)
{
    mTexture->renderTexture(renderer, mPosX, mPosY);
    if (mFrame % 2 == 0)
    {
        mShimmer->renderTexture(renderer, mPosX, mPosY);
    }
    mFrame++;
}

bool Particle::isDead()
{
    return mFrame > 10;
}