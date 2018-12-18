#ifndef __SPECIALSHAPE_H
#define __SPECIALSHAPE_H

#include <iostream>
#include "Point.h"
#include "GameBoard.h"

using namespace std;

enum eResult { False, True, FALSE_DEFAULT };

class SpecialShape
{
protected:
	Point body;
	char symbol;

public:

	SpecialShape(char symbol) : symbol(symbol) {}

	void setBody(const Point& head = FirstAppearance);

	virtual void goDown(const GameBoard& board,int& moveCounter) = 0;

	const Point& getBody() const;

	char getSymbol() const;

	void draw() const;

	void erase() const;

	virtual bool checkIfDownAvailable(const GameBoard& board) const =0 ;

	virtual eResult checkIfLRAvailable(char direction, const GameBoard& board) const = 0;

	virtual void move(char keyPressed, const GameBoard& board, int& moveCounter, bool& explode) = 0;

};

#endif __SHAPE_H