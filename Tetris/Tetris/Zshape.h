#ifndef __ZSHAPE_H
#define __ZSHAPE_H

#include "Point.h"
#include "GameBoard.h"
#include "Shape.h"

class Zshape : public Shape
{
	ePosition pos = downPos;
public:

	//Zshape(char symbol = 'Z') : Shape(symbol) {}

	virtual void setBody(const Point& head);

	virtual bool checkAvailabilityToRotate(const GameBoard &board) const;

	virtual void rotate(const GameBoard &board, int& moveCounter);

};

#endif __ZSHAPE_H