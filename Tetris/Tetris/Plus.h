#ifndef __PLUS_H
#define __PLUS_H

#include "Point.h"
#include "GameBoard.h"
#include "Shape.h"

class Plus : public Shape
{
	ePosition pos = upPos;
public:

	//Plus(char symbol = 'N') : Shape(symbol) {}

	virtual void setBody(const Point& head);

	bool checkAvailabilityToRotate(const GameBoard &board) const;

	void rotate(const GameBoard &board, int& moveCounter);

};

#endif __PLUS_H