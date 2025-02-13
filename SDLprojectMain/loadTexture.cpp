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

SDL_Texture* loadTexture::lTexture(std::string path, SDL_Renderer* renderer)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        logErrorAndExit("lTexture error", SDL_GetError());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            logErrorAndExit("lTexture error", SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}


int loadTexture::getHeight()
{
    return mHeight;
}

int loadTexture::getWidth()
{
    return mWidth;
}