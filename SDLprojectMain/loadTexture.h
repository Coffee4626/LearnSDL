#ifndef LOAD_TEXTURE_H
#define LOAD_TEXTURE_H

#include "GameBase.h"

class LoadTexture
{

public:
	LoadTexture();

	~LoadTexture();

	void Free();

	void renderTexture(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL);

	int getHeight();

	int getWidth();

	bool LoadFromRenderedText(std::string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer* gRenderer);

	bool LoadFromFile(std::string path, SDL_Renderer* gRenderer);


private:

	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;

};
#endif // !LOAD_TEXTURE_H

