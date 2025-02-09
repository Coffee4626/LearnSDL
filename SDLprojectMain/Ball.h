#ifndef BALL_H
#define BALL_H

#include "gameBase.h"

//constructor
//constant speed, location, direction
// parameterized constructor

class Ball
{

private:
	int ball_speed = 200;
	double x;
	//position for generation
	SDL_Rect position;

public:

	Ball();


};

//ball logic

//check collision

//bounce at panel

//bounce at wall

// bounce logic == geometry logic



#endif //!BALL_H

