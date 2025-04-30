#include "LoadTexture.h"
using namespace pong;
LoadTexture::LoadTexture()
{
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

LoadTexture::~LoadTexture()
{
	Free();
}

void LoadTexture::Free()
{
    if (mTexture != nullptr)
    {
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}


void LoadTexture::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LoadTexture::SetBlendMode(SDL_BlendMode mode)
{
	SDL_SetTextureBlendMode(mTexture, mode);
}

void LoadTexture::renderTexture(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip)
{
    SDL_Rect renderingSpace = { x, y, mWidth, mHeight };

    if (clip != NULL)
    {
        renderingSpace.w = clip->w;
        renderingSpace.h = clip->h;
    }

    SDL_RenderCopy(renderer, mTexture, clip, &renderingSpace);
}

TTF_Font* LoadTexture::LoadFont(const char* path, int size)
{
	TTF_Font* gFont = TTF_OpenFont(path, size);
	if (gFont == nullptr)
	{
		std::cout << "Unable to load a font for the application: " << TTF_GetError() << std::endl;
	}
	return gFont;
}


bool LoadTexture::LoadFromRenderedText(std::string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer* gRenderer)
{

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	Free();
	if (textSurface == NULL)
	{
		std::cout << "fail to load text texture" << std::endl;
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			std::cout << "Can not create texture from surface." << std::endl;
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	
	return mTexture != NULL;
}

bool LoadTexture::LoadFromFile(std::string path, SDL_Renderer* gRenderer)
{
	Free();

	SDL_Texture* tmpTexture = NULL;

	SDL_Surface* tmpSurface = IMG_Load(path.c_str());

	if (tmpSurface == NULL)
	{
		std::cout << path << std::endl;
		std::cout << IMG_GetError() << std::endl;
	}
	else
	{
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

		tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
		if (tmpTexture == NULL)
		{
			std::cout << path << std::endl;
			std::cout << IMG_GetError() << std::endl;
		}
		else
		{
			mWidth = tmpSurface->w;
			mHeight = tmpSurface->h;
		}
		SDL_FreeSurface(tmpSurface);
	}

	mTexture = tmpTexture;

	return mTexture != NULL;
}

int LoadTexture::getHeight()
{
    return mHeight;
}

int LoadTexture::getWidth()
{
    return mWidth;
}






