#include <iostream>
#include "Point.h"
#include "Gotoxy.h"
#include "Plus.h"
#include "GameBoard.h"
#include "Utils.h"

using namespace std;

void Plus::setBody(const Point& head)
{
	int x, y;

	x = head.getXCoordinate();
	y = head.getYCoordinate();

	if (pos == upPos)
	{

		body[0] = head;

		x--;
		y++;

		body[1].setXYCoordinate(x, y);

		x++;

		body[2].setXYCoordinate(x, y);

		x++;

		body[3].setXYCoordinate(x, y);
	}
	else if (pos == rightPos)
	{
	
		body[0].setXYCoordinate(x, y);

		x--;
		y--;

		body[1].setXYCoordinate(x, y);

		y++;

		body[2].setXYCoordinate(x, y);

		y++;

		body[3].setXYCoordinate(x, y);
	}
	else if (pos == downPos)
	{
	
		body[0].setXYCoordinate(x, y);

		x++;

		body[1].setXYCoordinate(x, y);

		x++;

		body[2].setXYCoordinate(x, y);

		x--;
		y++;

		body[3].setXYCoordinate(x, y);
	}
	else //leftPos
	{
		
		body[0].setXYCoordinate(x, y);

		y++;

		body[1].setXYCoordinate(x, y);

		y++;

		body[2].setXYCoordinate(x, y);

		x--;
		y--;

		body[3].setXYCoordinate(x, y);
	}
}
bool Plus::checkAvailabilityToRotate(const GameBoard & board) const
{
		int col = body[0].getXCoordinate();
		int row = body[0].getYCoordinate();

		if (pos == upPos)
		{
			if (board.getMatrixValueInCell(row + 2 - rowOffset, col - columnOffset) != -1)
			{
				return false;
			}
			return true;
		}
		else if(pos == rightPos)
		{
			if (col > 2)
			{
				if (board.getMatrixValueInCell(row - 1 - rowOffset, col - columnOffset) != -1 || board.getMatrixValueInCell(row-1-rowOffset,col-2-columnOffset) !=-1)
				{
					return false;
				}
				return true;
			}
			return false;
		}
		else if (pos == downPos)
		{
			if (board.getMatrixValueInCell(row + 1 - rowOffset, col - columnOffset) != -1)
			{
				return false;
			}
			return true;
		}
		else //pos == leftPos
		{
			if (col < 10)
			{
				if (board.getMatrixValueInCell(row + 1 - rowOffset, col + 1 - columnOffset)!= -1)
				{
					return false;
				}
				return true;
			}
			return false;
		}

	}
void Plus::rotate(const GameBoard &board, int& moveCounter)
{
	if (pos == downPos)
	{
		if (checkAvailabilityToRotate(board) == true)
		{
			pos = leftPos;

			erase();

			int x = body[0].getXCoordinate();

			x++;

			body[0].setXCoordinate(x);

			setBody(getPointFromBody(0));

			draw();
		}
		else
		{
			goDown(moveCounter);
		}
	}
	else if(pos == leftPos)
	{
		if (checkAvailabilityToRotate(board) == true)
		{
			pos = upPos;

			erase();

			setBody(getPointFromBody(0));

			draw();
		}
		else
		{
			goDown(moveCounter);
		}
	}

	else if (pos == upPos)
	{
		if (checkAvailabilityToRotate(board) == true)
		{
			pos = rightPos;

			erase();

			int x = body[0].getXCoordinate();
			int y = body[0].getYCoordinate();

			x++;
			y++;

			body[0].setXYCoordinate(x, y);

			setBody(getPointFromBody(0));

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

			int x = body[0].getXCoordinate();
			int y = body[0].getYCoordinate();

			x = x - 2;
			y--;

			body[0].setXYCoordinate(x, y);

			setBody(getPointFromBody(0));

			draw();
		}
		else
		{
			goDown(moveCounter);
		}
	}
}
