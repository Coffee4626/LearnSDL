#include "loadTexture.h"

loadTexture::loadTexture()
{
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

void loadTexture::Free()
{
    if (mTexture != nullptr)
    {
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

loadTexture::~loadTexture()
{
    Free();
}


void loadTexture::renderTexture(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip)
{
    SDL_Rect renderingSpace = { x, y, mWidth, mHeight };

    if (clip != NULL)
    {
        renderingSpace.w = clip->w;
        renderingSpace.h = clip->h;
    }

    SDL_RenderCopy(renderer, mTexture, clip, &renderingSpace);
}

int loadTexture::getHeight()
{
    return mHeight;
}

int loadTexture::getWidth()
{
    return mWidth;
}