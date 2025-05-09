#ifndef PARTICLE_H
#define PARTICLE_H
#include "GameBase.h"
//namespace pong
//{
//
//    class Particle
//    {
//    public:
//		struct Velocity
//		{
//			float x;
//			float y;
//		};
//
//		struct Position
//		{
//			float x;
//			float y;
//		};
//        Particle(float x, float y, int life, float angle, int speed, int size, SDL_Color color);
//		void Update(float deltaTime);
//    private:
//		int mLifespan;
//		Velocity mVelocity;
//		Position mPosition;
//        SDL_Color color;
//    };
//}

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