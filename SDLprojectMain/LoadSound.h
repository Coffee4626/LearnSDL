#ifndef LOAD_SOUND_H
#define LOAD_SOUND_H

#include <SDL_mixer.h>
#include <iostream>
#include <string>
namespace pong
{
	class Sound
	{
	public:
		Sound();
		~Sound();
		void Free();
		Mix_Chunk* LoadSound(std::string path);
		void SetVolume(int volume);
		int GetVolume() const;
		void PlaySound(int channel, int loops, int volume);
		void StopSound(int channel);
	private:
		Mix_Chunk* mChunk;
		int mVolume;
	};
}


#endif // !LOAD_SOUND_H
