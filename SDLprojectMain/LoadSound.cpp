//#include "LoadSound.h"
//#include <iostream>
//
//Sound::Sound()
//{
//	mChunk = nullptr;
//	mVolume = 128; // Default volume (0-128)
//}
//
//Sound::~Sound()
//{
//	Free();
//}
//
//void Sound::Free()
//{
//	if (mChunk != nullptr)
//	{
//		Mix_FreeChunk(mChunk);
//		mChunk = nullptr;
//	}
//}
//
//Mix_Chunk* Sound::LoadSound(const char* path)
//{
//	Mix_Chunk* sound = Mix_LoadWAV(path);
//	if (sound == nullptr)
//	{
//		std::cout << "Unable to load sound: " << Mix_GetError() << std::endl;
//		return nullptr;
//	}
//	return sound;
//}
//
//Mix_Music* Sound::LoadMusic(const char* path)
//{
//	Mix_Music* music = Mix_LoadMUS(path);
//	if (music == nullptr)
//	{
//		std::cout << "Unable to load music: " << Mix_GetError() << std::endl;
//		return nullptr;
//	}
//	return music;
//}
//
//void Sound::PlaySound(const std::string& soundId, int channel, int loops)
//{
//	if (mChunk == nullptr)
//	{
//		std::cout << "No sound loaded to play." << std::endl;
//		return;
//	}
//	Mix_PlayChannel(channel, mChunk, loops);
//}
//
//void Sound::StopSound(int channel)
//{
//	Mix_HaltChannel(channel);
//}