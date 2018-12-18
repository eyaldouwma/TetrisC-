#include "Gotoxy.h"
#include "Joker.h"
#include <iostream>
#include "Utils.h"

using namespace std;

// the documentation of some of the methods is similar to the bomb's (because of thier same size etc.)

eResult Joker::checkIfLRAvailable(char Key, const GameBoard& board) const
{
	int x = body.getXCoordinate();

	switch (Key)
	{
	case Left: //left
	{
		if (x > 1)
		{
			return True;
		}
		else
		{
			return False;
		}
	}
	case Right: //right
	{
		if (x < 10)
		{
			return True;
		}
		else
		{
			return False;
		}
	}
	default:
		return False;
	}
}

bool Joker::checkIfDownAvailable(const GameBoard& board) const
{
	int y = body.getYCoordinate();

	if (y < 18)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Joker::move(char keyPressed, const GameBoard& board, int& moveCounter, bool& explode)
{
	int x, y;
	char symbolSaver;

	switch (keyPressed)
	{
	case Left: //left
	{
		if (checkIfLRAvailable(keyPressed,board) == True)
		{
			moveCounter++;
			x = body.getXCoordinate();
			y = body.getYCoordinate();

			symbolSaver = board.getMatrixValueInCell(y - rowOffset, x - columnOffset);

			if (symbolSaver != -1)
			{
				gotoxy(x, y);
				cout << symbolSaver;
			}
			else
			{
				erase();
			}

			x--;
			body.setXCoordinate(x);

			draw();
		}
		else
		{
			goDown(board, moveCounter);
		}
		break;
	}
	case Right: //right
	{
		if (checkIfLRAvailable(keyPressed,board) == True)
		{
			moveCounter++;
			x = body.getXCoordinate();
			y = body.getYCoordinate();

			symbolSaver = board.getMatrixValueInCell(y - rowOffset, x - columnOffset);

			if (symbolSaver != -1)
			{
				gotoxy(x, y);
				cout << symbolSaver;
			}
			else
			{
				erase();
			}
			x++;
			body.setXCoordinate(x);

			draw();
		}
		else
		{
			goDown(board, moveCounter);
		}
		break;
	}
	case Down: //straight down
	{
		x = body.getXCoordinate();
		y = body.getYCoordinate();

		symbolSaver = board.getMatrixValueInCell(y - rowOffset, x - columnOffset);

		erase();

		gotoxy(x, y);
		cout << symbolSaver;

		y = 18;
		body.setYCoordinate(y);

		draw();
		break;
	}
	default: //down
	{
		goDown(board, moveCounter);
		break;
	}
	}
}
void Joker::goDown(const GameBoard& board, int& moveCounter)
{
	moveCounter = 0;
	int x = body.getXCoordinate();
	int y = body.getYCoordinate();

	char symbolSaver = board.getMatrixValueInCell(y - rowOffset, x - columnOffset);  //the symbol which the joker is "sitting on" now.

	if (symbolSaver != -1) // we want to draw this symbol again on the board, after the joker will continue down.
	{
		gotoxy(x, y);
		cout << symbolSaver;
	}
	else
	{
		erase();
	}
	y++;

	body.setYCoordinate(y);

	draw();
}