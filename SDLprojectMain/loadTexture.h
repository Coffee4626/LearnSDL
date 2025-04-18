#ifndef LOAD_TEXTURE_H
#define LOAD_TEXTURE_H

#include "GameBase.h"
namespace pong
{
	class LoadTexture
	{

	public:
		LoadTexture();

		~LoadTexture();

		bool LoadFromRenderedText(std::string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer* gRenderer);
		
		bool LoadFromFile(std::string path, SDL_Renderer* gRenderer);
		
		void Free();

		void renderTexture(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL);

		void SetBlendMode(SDL_BlendMode mode);

		void SetAlpha(Uint8 alpha);
		
		int getHeight();

		int getWidth();

	private:

		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;

	};
}
#endif // !LOAD_TEXTURE_H

