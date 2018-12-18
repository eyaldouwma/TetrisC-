#include <iostream>
#include "Point.h"
#include "Gotoxy.h"
#include "Snake.h"
#include "Utils.h"

using namespace std;

void Snake::setBody(const Point& head) // sets the snake in a new place on board
{
	int x, y;

	//the method gets a new head and sets the whole body accordingly

	x = head.getXCoordinate();
	y = head.getYCoordinate();
	
	if (pos==downPos)
	{
		for (int i = 0; i < ShapeSize; i++)
		{
			body[i].setXYCoordinate(x, y);
			x++;
		}
	}
	else
	{
		for (int i = 0; i < ShapeSize; i++)
		{
			body[i].setXYCoordinate(x, y);
			y++;
		}
	}
}
bool Snake::checkAvailabilityToRotate(const GameBoard &board) const
{
	int row, col;
	col = body[0].getXCoordinate();
	row = body[0].getYCoordinate();

	if (pos==downPos) // the snake lays down
	{
		if (row < 16)
		{
			for (int i = 1; i < ShapeSize; i++)
			{
				if (board.getMatrixValueInCell(row - rowOffset + i, col - columnOffset) != -1)
					return false;
			}
			return true;
		}
		return false;
	}
	else // it is vertical
	{
		if (col < 8)
		{
			for (int i = 1; i < 4; i++)
			{
				if (board.getMatrixValueInCell(row - rowOffset, col - columnOffset + i) != -1)
					return false;
			}
			return true;
		}
		return false;
	}
}
void Snake::rotate(const GameBoard& board, int& moveCounter)
{
	int x, y;

	x = body[0].getXCoordinate();
	y = body[0].getYCoordinate();

	if (pos==downPos)
	{
		if (checkAvailabilityToRotate(board) == true)
		{
			pos = upPos;

			erase();

			setBody(body[0]);

			draw();
		}
		else
		{
			goDown(moveCounter);
		}
	}
	else //pos == upPos
	{
		if (checkAvailabilityToRotate(board) == true)
		{
			pos = downPos;

			erase();

			setBody(body[0]);

			draw();
		}
		else
		{
			goDown(moveCounter);
		}
	}
}


