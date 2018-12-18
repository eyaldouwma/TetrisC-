#include <iostream>
#include "Point.h"
#include "Gotoxy.h"
#include "Square.h"
#include "GameBoard.h"
#include "Utils.h"

using namespace std;

void Square::setBody(const Point& head)
{
	int x, y;

	x = head.getXCoordinate();
	y = head.getYCoordinate();

	body[0] = head;

	x++;

	body[1].setXYCoordinate(x, y);

	x--;
	y++;

	body[2].setXYCoordinate(x, y);

	x++;

	body[3].setXYCoordinate(x, y);
}

void Square::rotate(const GameBoard &board, int& moveCounter)
{
	goDown(moveCounter);
}