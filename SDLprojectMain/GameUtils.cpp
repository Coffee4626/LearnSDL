#include "GameUtils.h"

GraphicalTimer::GraphicalTimer()
{
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

void GraphicalTimer::start()
{
	mStarted = true;
	mPaused = false;

	mStartTicks = SDL_GetTicks64();
	mPausedTicks = 0;
}

void GraphicalTimer::reset()
{
	mStarted = false;
	mPaused = false;

	mStartTicks = 0;
	mPausedTicks = 0;
}

void GraphicalTimer::pause()
{
	if (mStarted && !mPaused)
	{
		mPaused = true;
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void GraphicalTimer::unpause()
{
	if (mStarted && mPaused)
	{
		mPaused = false;
		mStartTicks = mPausedTicks - SDL_GetTicks();
		mPausedTicks = 0;
	}
}

Uint32 GraphicalTimer::GetTicks()
{
	Uint32 time = 0;
	
	if (mStarted)
	{
		if (mPaused)
		{
			time = mPausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - mStartTicks;
		}
	}
	return time;
}

bool GraphicalTimer::IsPaused()
{
	return mPaused && mStarted;
}

bool GraphicalTimer::IsStarted()
{
	return mStarted;
}