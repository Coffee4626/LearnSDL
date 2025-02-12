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

SDL_Texture* loadTexture::lTexture(const char* filename, SDL_Renderer* renderer)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
    }

    return texture;
}


int loadTexture::getHeight()
{
    return mHeight;
}

int loadTexture::getWidth()
{
    return mWidth;
}