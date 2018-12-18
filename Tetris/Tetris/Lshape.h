#ifndef __LSHAPE_H
#define __LSHAPE_H

#include "Point.h"
#include "GameBoard.h"
#include "Shape.h"

class Lshape : public Shape
{
	ePosition pos = downPos;

public:

	//Lshape(char symbol = 'X') : Shape(symbol) {}

	virtual void setBody(const Point& head);

	virtual bool checkAvailabilityToRotate(const GameBoard &board) const;

	virtual void rotate(const GameBoard &board, int& moveCounter);

};

#endif __LSHAPE_H