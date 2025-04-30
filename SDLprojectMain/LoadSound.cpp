#include "LoadSound.h"
#include <iostream>
using namespace pong;

Sound::Sound()
{
	mChunk = nullptr;
	mVolume = 128; 
}

Sound::~Sound()
{
	Free();
}

void Sound::Free()
{
	if (mChunk != nullptr)
	{
		Mix_FreeChunk(mChunk);
		mChunk = nullptr;
	}
}

void Sound::SetVolume(int volume)
{
	mVolume = volume;
	Mix_Volume(-1, mVolume);
}

int Sound::GetVolume() const
{
	return mVolume;
}

Mix_Chunk* Sound::LoadSound(std::string path)
{
	Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
	if (sound == nullptr)
	{
		std::cout << "Unable to load sound: " << Mix_GetError() << std::endl;
		return nullptr;
	}
	mChunk = sound;
	return mChunk;
}

void Sound::PlaySound(int channel, int loops, int volume)
{
	if (mChunk == nullptr)
	{
		std::cout << "No sound loaded to play." << std::endl;
		return;
	}
	SetVolume(volume);
	Mix_PlayChannel(channel, mChunk, loops);
}

void Sound::StopSound(int channel)
{
	Mix_HaltChannel(channel);
}