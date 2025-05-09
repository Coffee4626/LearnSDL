//#include "ParticleEngine.h"
//
//using namespace pong;
//
//ParticleEngine::ParticleEngine() 
//{
//
//}
//
//void ParticleEngine::Emit(float x, float y, int count, SDL_Color color) 
//{
//    for (int i = 0; i < count; ++i) 
//    {
//        float velX = (rand() % 200 - 100) / 100.0f;
//        float velY = (rand() % 200 - 100) / 100.0f;
//        int lifespan = rand() % 500 + 500;
//        mParticles.emplace_back(x, y, velX, velY, color, lifespan);
//    }
//}
//
//void ParticleEngine::Update(float deltaTime) 
//{
//    for (auto it = mParticles.begin(); it != mParticles.end();) 
//    {
//        it->Update(deltaTime);
//        if (!it->IsAlive()) 
//        {
//            it = mParticles.erase(it);
//        }
//        else 
//        {
//            ++it;
//        }
//    }
//}
//
//void ParticleEngine::Render(SDL_Renderer* renderer) 
//{
//    for (auto& particle : mParticles) 
//    {
//		particle.Render(renderer);
//    }
//}