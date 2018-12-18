#ifndef __BOMB_H
#define __BOMB_H
#include "Point.h"
#include "GameBoard.h"
#include "SpecialShape.h"

class Bomb : public SpecialShape
{
public:
	Bomb(char symbol = '@') : SpecialShape(symbol) {}

	virtual eResult checkIfLRAvailable(char Key,const GameBoard& board) const;

	virtual bool checkIfDownAvailable(const GameBoard& board) const;

	void move(char KeyPressed,const GameBoard& board,int& moveCounter,bool& explode);

	int explode(GameBoard &board);

	virtual void goDown(const GameBoard& board,int& moveCounter);



};

#endif __BOMB_H



