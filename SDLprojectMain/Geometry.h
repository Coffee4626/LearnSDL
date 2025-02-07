#ifndef Geometry
#define Geometry

#include "gameBase.h"

class Point
{
public:
	int x, y;

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
		int temp1 = (l1.p1.x * l1.p2.y) - (l1.p1.y * l1.p2.x);
		int temp2 = (l2.p1.x * l2.p2.y) - (l2.p1.y * l2.p2.x);
		// Intersection point P
		int x1 = temp1 * (l2.p1.x - l2.p2.x) - (l1.p1.x - l1.p2.x) * temp2;
		int y1 = ((l1.p1.x - l1.p2.x) * (l2.p1.y - l2.p2.y)) - ((l1.p1.y - l1.p2.y) * (l2.p1.x - l2.p2.x));
		int x2 = temp1 * (l2.p1.y - l2.p2.y) - (l1.p1.y - l1.p2.y) * temp2;
		int y2 = ((l1.p1.x - l1.p2.x) * (l2.p1.y - l2.p2.y)) - ((l1.p1.y - l1.p2.y) * (l2.p1.x - l2.p2.x));
		return Point(x1 / y1, x2 / y2);
	}

	bool checkPointOnLine(Line l1, Point p)
	{

	}


	//Compute perpendicular bisector

};


#endif // !Geometry

