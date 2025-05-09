#ifndef PARTICLE_H
#define PARTICLE_H
#include "GameBase.h"

namespace pong
{
	class Particle
	{
	public:
		Particle(int x, int y, LoadTexture* texture, LoadTexture* shimmer);
		void Render(SDL_Renderer* renderer);
		bool isDead();
	private:
		int mPosX, mPosY;
		int mFrame;
		LoadTexture* mTexture;
		LoadTexture* mShimmer;
	};
}
#endif // !PARTICLE_H