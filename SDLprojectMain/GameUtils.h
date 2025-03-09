#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include "GameBase.h"

class GraphicalTimer
{
public:
	GraphicalTimer();

	void start();
	void pause();
	void unpause();
	void reset();

	Uint32 GetTicks();
	bool IsStarted();
	bool IsPaused();

private:
	Uint32 mStartTicks;
	Uint32 mPausedTicks;

	bool mPaused;
	bool mStarted;
};

#endif // !GAME_UTILS_H
