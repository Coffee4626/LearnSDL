#include "EventHandle.h"
#include "InputHandle.h"
void gameEvents()
{
	bool quit = false;
	while (!quit)
	{
		//fps


		//event
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			//input
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}



		//logic




		//render


	}
	SDL_Quit();
}