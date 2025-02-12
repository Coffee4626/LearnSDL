#ifndef LOAD_TEXTURE_H
#define LOAD_TEXTURE_H

#include "gameBase.h"

class loadTexture
{

public:
	loadTexture();

	~loadTexture();

	void Free();

	void renderTexture(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL);

	int getHeight();

	int getWidth();

	SDL_Texture* lTexture(const char* filename, SDL_Renderer* renderer);


private:

	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;

};
#endif // !LOAD_TEXTURE_H

