#ifndef Geometry
#define Geometry

#include "gameBase.h"

class Vector2D
{
public:
	float x;
	float y;
	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2D(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	Vector2D operator+ (Vector2D const& other)
	{
		return Vector2D(x + other.x, y + other.y);
	}
	Vector2D operator* (float scalar)
	{
		return Vector2D(x * scalar, y * scalar);
	}
};

class Point
{
public:
	float x, y;

	Point()
	{
		this->x = 0;
		this->y = 0;
	}

	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void setPoint(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	Point getPoint()
	{
		return Point(x, y);
	}
};

class Line
{
public:
	Point p1, p2;

	Line()
	{

	}

	Line(Point p1, Point p2)
	{
		this->p1 = p1;
		this->p2 = p2;
	}

	void setLine(Point p1, Point p2)
	{
		this->p1 = p1;
		this->p2 = p2;
	}

	Line getLine()
	{
		return Line(p1, p2);
	}
};


class Calc
{
public:

	//Dot product



	//Cross product



	//Calculate point of intersection
	Point linesIntersection(Line l1, Line l2)
	{
		//Calculating determinant
		//https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection#Given_two_points_on_each_line
		float temp1 = (l1.p1.x * l1.p2.y) - (l1.p1.y * l1.p2.x);
		float temp2 = (l2.p1.x * l2.p2.y) - (l2.p1.y * l2.p2.x);
		// Intersection point P
		float x1 = temp1 * (l2.p1.x - l2.p2.x) - (l1.p1.x - l1.p2.x) * temp2;
		float y1 = ((l1.p1.x - l1.p2.x) * (l2.p1.y - l2.p2.y)) - ((l1.p1.y - l1.p2.y) * (l2.p1.x - l2.p2.x));
		float x2 = temp1 * (l2.p1.y - l2.p2.y) - (l1.p1.y - l1.p2.y) * temp2;
		float y2 = ((l1.p1.x - l1.p2.x) * (l2.p1.y - l2.p2.y)) - ((l1.p1.y - l1.p2.y) * (l2.p1.x - l2.p2.x));
		return Point(x1 / y1, x2 / y2);
	}

	bool checkPointOnLine(Line l1, Point p)
	{

	}


	//Compute perpendicular bisector

};

//accleration for paddle and ball
#endif // !Geometry

