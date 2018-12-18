#ifndef __SNAKE_H
#define __SNAKE_H

#include "Point.h"
#include "GameBoard.h"
#include "Shape.h"

class Snake : public Shape
{
private:
	ePosition pos = downPos;
public:

	//Snake(char symbol = 'O') : Shape(symbol) {}

	virtual void setBody(const Point& head);

	virtual bool checkAvailabilityToRotate(const GameBoard &board) const;

	virtual void rotate(const GameBoard &board,int& moveCounter);


};

#endif __Snake_H


