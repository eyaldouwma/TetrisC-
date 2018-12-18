#ifndef __JOKER_H
#define __JOKER_H

#include "Point.h"
#include "GameBoard.h"
#include "SpecialShape.h"

class Joker : public SpecialShape
{
public:
	
	Joker(char symbol = '$') : SpecialShape(symbol) {}

	virtual eResult checkIfLRAvailable(char direction, const GameBoard& board) const;
	
	virtual bool checkIfDownAvailable(const GameBoard& board) const;
	
	virtual void goDown(const GameBoard& board, int& moveCounter);

	virtual void move(char keyPressed, const GameBoard& board, int& moveCounter, bool& explode);
};

#endif __JOKER_H
