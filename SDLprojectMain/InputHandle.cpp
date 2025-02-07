#include "InputHandle.h"
#include "Geometry.h"
void InputHandle(SDL_Event event)
{
	int initialMouseX, initialMouseY;
	int currentMouseX, currentMouseY;
	bool draw = false;
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		draw = true;
		SDL_GetMouseState(&initialMouseX, &initialMouseY);
		Point p1 = Point (initialMouseX, initialMouseY);
		
	}

	if (event.type == SDL_MOUSEBUTTONUP)
	{
		draw = false;
	}

}


