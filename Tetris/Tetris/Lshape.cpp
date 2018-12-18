#include <iostream>
#include "Point.h"
#include "Gotoxy.h"
#include "Lshape.h"
#include "GameBoard.h"
#include "Utils.h"

using namespace std;

void Lshape::setBody(const Point& head)
{

	int x, y;

	x = head.getXCoordinate();
	y = head.getYCoordinate();

	if (pos == upPos)
	{
		body[0] = head;

		y++;

		body[1].setXYCoordinate(x, y);

		x++;

		body[2].setXYCoordinate(x, y);

		x++;

		body[3].setXYCoordinate(x, y);
	}

	else if (pos == rightPos)
	{
		body[0] = head;

		x--;

		body[1].setXYCoordinate(x, y);

		y++;

		body[2].setXYCoordinate(x, y);

		y++;

		body[3].setXYCoordinate(x, y);
	}

	else if (pos == downPos)
	{
		body[0] = head;

		y--;

		body[1].setXYCoordinate(x, y);

		x--;

		body[2].setXYCoordinate(x, y);

		x--;

		body[3].setXYCoordinate(x, y);
	}
	else if (pos == leftPos)
	{
		body[0] = head;

		x++;

		body[1].setXYCoordinate(x, y);

		y--;

		body[2].setXYCoordinate(x, y);

		y--;

		body[3].setXYCoordinate(x, y);
	}

}

bool Lshape::checkAvailabilityToRotate(const GameBoard & board) const
{
	int col = body[0].getXCoordinate();
	int row = body[0].getYCoordinate();

	if (pos == upPos)
	{
		if (col > 1)
		{
			if (board.getMatrixValueInCell(row - rowOffset, col - 1 - columnOffset) != -1 || board.getMatrixValueInCell(row +1 - rowOffset, col - 1 - columnOffset) != -1 || board.getMatrixValueInCell(row+2-rowOffset,col-1-columnOffset)!=-1)
			{
				return false;
			}
			return true;
		}
		return false;
	}

	else if (pos == rightPos)
	{
		if (col > 2 && row > 4)
		{
			if (board.getMatrixValueInCell(row - rowOffset, col + 1 - columnOffset) != -1 || board.getMatrixValueInCell(row + 1 - rowOffset, col + 1 - rowOffset) != -1)
			{
				return false;
			}
			return true;
		}
		return false;
	}
	else if (pos == downPos)
	{
		if (row > 5 && col < 10)
		{
			if (board.getMatrixValueInCell(row - rowOffset, col + 1 - columnOffset) != -1 || board.getMatrixValueInCell(row - 1 - rowOffset, col + 1 - columnOffset) != -1 || board.getMatrixValueInCell(row - 2 - rowOffset, col + 1 - columnOffset)!=-1)
			{
				return false;
			}
			return true;
		}
		return false;
	}
	else // pos == leftPos
	{
		if (col < 9)
		{
			if (board.getMatrixValueInCell(row + 1 - rowOffset, col - columnOffset) !=-1 || board.getMatrixValueInCell(row + 1- rowOffset, col + 1 - columnOffset) !=-1 || board.getMatrixValueInCell(row + 1 - rowOffset, col + 2 - columnOffset) != -1)
			{
				return false;
			}
			return true;
		}
		return false;
	}

}

void Lshape::rotate(const GameBoard & board, int & moveCounter)
{
	if (pos == upPos)
	{
		if (checkAvailabilityToRotate(board) == true)
		{
			pos = rightPos;

			erase();

			setBody(body[0]);

			draw();
		}
		else
		{
			goDown(moveCounter);
		}
	}
	else if (pos == rightPos)
	{
		if (checkAvailabilityToRotate(board) == true)
		{
			pos = downPos;

			erase();

			setBody(getPointFromBody(0));

			draw();
		}
		else
		{
			goDown(moveCounter);
		}
	}
	else if (pos == downPos)
	{
		if (checkAvailabilityToRotate(board) == true)
		{
			pos = leftPos;

			erase();

			setBody(getPointFromBody(0));

			draw();
		}
		else
		{
			goDown(moveCounter);
		}
	}
	else //leftPos
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

}
