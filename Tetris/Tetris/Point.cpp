#include "Point.h"

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}
void Point::setXCoordinate(int x)
{
	this->x = x;
}
void Point::setYCoordinate(int y)
{
	this->y = y;
}
void Point::setXYCoordinate(int x, int y)
{
	this->x = x;
	this->y = y;
}