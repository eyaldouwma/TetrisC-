#ifndef __SQUARE_H
#define __SQUARE_H

#include "Point.h"
#include "GameBoard.h"
#include "Shape.h"

class Square : public Shape
{

public:

	//Square(char symbol = '#') : Shape(symbol) {}

	virtual void setBody(const Point& head);

	virtual bool checkAvailabilityToRotate(const GameBoard &board) const { return false; }

	virtual void rotate(const GameBoard &board, int& moveCounter);

};

#endif __SQUARE_H