#ifndef __SHAPE_H
#define __SHAPE_H

#include <iostream>
#include "Point.h"
#include "GameBoard.h"

using namespace std;

enum ePosition{upPos, downPos, leftPos, rightPos};

class Shape
{
protected:
	Point body[ShapeSize];
	char symbol;

public:
	
	Shape(char symbol = 'O') : symbol(symbol) {}

	char getSymbol() const;

	virtual void setBody(const Point& head = FirstAppearance) = 0;

	const Point* getBody() const;

	const Point& getPointFromBody(int i) const;

	void draw() const;

	void erase() const;

	bool checkIfLRAvailable(char direction, const GameBoard& board) const;

	bool checkIfDownAvailable(const GameBoard& board) const;

	void goDown(int& moveCounter);

	void move(char direction, const GameBoard &board, int& moveCounter);

	virtual bool checkAvailabilityToRotate(const GameBoard &board) const = 0 ;

	virtual void rotate(const GameBoard &board, int& moveCounter) = 0;
};

#endif __SHAPE_H