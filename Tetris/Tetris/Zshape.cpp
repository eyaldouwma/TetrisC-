#include <iostream>
#include "Point.h"
#include "Gotoxy.h"
#include "Zshape.h"
#include "GameBoard.h"
#include "Utils.h"

using namespace std;

void Zshape::setBody(const Point& head)
{
	int x, y;

	x = head.getXCoordinate();
	y = head.getYCoordinate();

	if (pos == downPos)
	{
		body[0].setXYCoordinate(x, y);

		x++;

		body[1].setXYCoordinate(x, y);

		y++;

		body[2].setXYCoordinate(x, y);

		x++;

		body[3].setXYCoordinate(x, y);
	}
	else //upPos
	{
		
		body[0].setXYCoordinate(x, y);

		y++;

		body[1].setXYCoordinate(x, y);

		x--;

		body[2].setXYCoordinate(x, y);

		y++;

		body[3].setXYCoordinate(x, y);
	}
}

bool Zshape::checkAvailabilityToRotate(const GameBoard & board) const
{
	int col = body[0].getXCoordinate();
	int row = body[0].getYCoordinate();

	if (pos == downPos)
	{
		if (row > 4)
		{
			if ((board.getMatrixValueInCell(row + 1 - rowOffset, col - columnOffset) != -1) || (board.getMatrixValueInCell(row - 1 - rowOffset, col + 1 - columnOffset) != -1))
			{
				return false;
			}
			return true;
		}
		return false;
	}
	else
	{
		if (col < 10)
		{
			if ((board.getMatrixValueInCell(row + 2 - rowOffset, col - columnOffset) != -1) || (board.getMatrixValueInCell(row + 2 - rowOffset, col + 1 - columnOffset) != -1))
			{
				return false;
			}
			return true;
		}
		return false;
	}
}
void Zshape::rotate(const GameBoard & board, int & moveCounter)
{
	if (pos == downPos)
	{
		if (checkAvailabilityToRotate(board) == true)
		{
			pos = upPos;

			erase();

			int x = body[0].getXCoordinate();
			int y = body[0].getYCoordinate();

			x++;
			y--;

			body[0].setXYCoordinate(x, y);

			setBody(body[0]);

			draw();
		}
		else
		{
			goDown(moveCounter);
		}
	}
	else
	{
		if (checkAvailabilityToRotate(board) == true)
		{
			pos = downPos;

			erase();

			int x = body[0].getXCoordinate();
			int y = body[0].getYCoordinate();

			x--;
			y++;

			body[0].setXYCoordinate(x, y);

			setBody(body[0]);

			draw();
		}
		else
		{
			goDown(moveCounter);
		}
	}
}
