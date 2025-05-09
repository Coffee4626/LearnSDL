#include "Particle.h"

using namespace pong;

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