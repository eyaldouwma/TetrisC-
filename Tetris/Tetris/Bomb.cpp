#include "Gotoxy.h"
#include "Bomb.h"
#include <iostream>
#include "Utils.h"

using namespace std;

eResult Bomb::checkIfLRAvailable(char Key,const GameBoard& board) const //check if there is room for the bomb to move right or left
{
	int col = body.getXCoordinate();
	int row = body.getYCoordinate();

	switch (Key)
	{
	case Left: //left
	{
		if (col > 1)
		{
			if (board.getMatrixValueInCell(row - rowOffset, col - (1+columnOffset)) == -1)
				return True;
		}
		else if (col == 1)
		{
			return FALSE_DEFAULT;
		}
		return False;
	}
	case Right: //right
	{
		if (col < 10)
		{
			if (board.getMatrixValueInCell(row - rowOffset, col) == -1)
				return True;
		}
		else if (col == 10)
		{
			return FALSE_DEFAULT;
		}
		return False;
	}
	default:
		return FALSE_DEFAULT;
	}
}

bool Bomb::checkIfDownAvailable(const GameBoard& board) const 
{
	int col = body.getXCoordinate();
	int row = body.getYCoordinate();

	if (row < 18)
	{
		if (board.getMatrixValueInCell(row - (rowOffset-1), col - columnOffset) == -1)
			return true;
	}
	return false;
}

void Bomb::move(char keyPressed,const GameBoard& board,int& moveCounter, bool& explode) // move down/left/right due to what the user wanted
{
	int x, y;

	switch (keyPressed)
	{
	case Left: //left
	{
		if (checkIfLRAvailable(keyPressed, board) == True)
		{
			moveCounter++;
			x = body.getXCoordinate();

			x--;
			erase();

			body.setXCoordinate(x);
			draw();
		}
		else if (checkIfLRAvailable(keyPressed, board) == FALSE_DEFAULT)
		{
			goDown(board,moveCounter);
		}
		else
		{
			explode = true;
		}
		break;
	}
	case Right: //right
	{
		if (checkIfLRAvailable(keyPressed, board) == True)
		{
			moveCounter++;
			x = body.getXCoordinate();

			x++;

			erase();

			body.setXCoordinate(x);

			draw();
		}
		else if (checkIfLRAvailable(keyPressed, board) == FALSE_DEFAULT)
		{
			goDown(board, moveCounter);
		}
		else
		{
			explode = true;
		}
		break;
	}
	case Down: //straight down
	{
		y = body.getYCoordinate();
		erase();
		while (checkIfDownAvailable(board))
		{
			y++;
			body.setYCoordinate(y);
		}
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
int Bomb::explode(GameBoard &board) //return how many tiles exploded
{
	int counter = 0;

	int i, j;

	int col = body.getXCoordinate();
	int row = body.getYCoordinate();


	if (col == 10)// right wall
	{
		if (row == 18) //right lower corner
		{
			for (i = row - 1; i < 19; i++)
			{
				for (j = col - 1; j < 11;j++)
				{
					if (board.getMatrixValueInCell(i - rowOffset, j - columnOffset) != -1 && board.getMatrixValueInCell(i - rowOffset, j - columnOffset) != '@')
					{
						counter++;
						gotoxy(j, i);
						cout << ' ';
						board.setMatrixValueCell(i - rowOffset, j - columnOffset, -1);
					}
				}
			}
		}
		else //only right wall
		{
			for (i = row - 1; i < row + 2;i++)
			{
				for (j = col - 1; j < col + 1;j++)
				{
					if (board.getMatrixValueInCell(i - rowOffset, j - columnOffset) != -1 && board.getMatrixValueInCell(i - rowOffset, j - columnOffset) != '@')
					{
						counter++;
						gotoxy(j, i);
						cout << ' ';
						board.setMatrixValueCell(i - rowOffset, j - columnOffset, -1);
					}
				}
			}
		}
	}
	else if (col == 1) //left wall
	{
		if (row == 18) //left lower corner
		{
			for (i = row - 1; i < row + 1;i++)
			{
				for (j = col; j < col + 2;j++)
				{
					if (board.getMatrixValueInCell(i - rowOffset, j - columnOffset) != -1 && board.getMatrixValueInCell(i - rowOffset, j - columnOffset) != '@')
					{
						counter++;
						gotoxy(j, i);
						cout << ' ';
						board.setMatrixValueCell(i - rowOffset, j - columnOffset, -1);
					}
				}
			}
		}
		else //only left wall
		{
			for (i = row+1; i < row + 2;i++)
			{
				for (j = col; j < col + 2;j++)
				{
					if (board.getMatrixValueInCell(i - rowOffset, j -columnOffset) != -1 && board.getMatrixValueInCell(i - rowOffset, j - columnOffset) != '@')
					{
						counter++;
						gotoxy(j, i);
						cout << ' ';
						board.setMatrixValueCell(i - rowOffset, j - columnOffset, -1);
					}
				}
			}
		}
	}
	else if (row == 18) //floor
	{
		for (i = row - 1; i < row + 1; i++)
		{
			for (j = col - 1; j < col + 2; j++)
			{
				if (board.getMatrixValueInCell(i - rowOffset, j - columnOffset) != -1 && board.getMatrixValueInCell(i - rowOffset, j - columnOffset) != '@')
				{
					counter++;
					gotoxy(j, i);
					cout << ' ';
					board.setMatrixValueCell(i - rowOffset, j - columnOffset, -1);
				}
			}
		}
	}
	else if (row == 4) //ceiling
	{
		for (i = row; i < row + 2; i++)
		{
			for (j = col - 1; j < col + 2; j++)
			{
				if (board.getMatrixValueInCell(i - rowOffset, j - columnOffset) != -1 && board.getMatrixValueInCell(i - rowOffset, j - columnOffset) != '@')
				{
					counter++;
					gotoxy(j, i);
					cout << ' ';
					board.setMatrixValueCell(i - rowOffset, j - columnOffset, -1);
				}
			}
		}
	}
	else
	{	
		for (i = row - 1; i < row + 2; i++)
		{
			for (j = col - 1; j < col + 2; j++)
			{
				if (board.getMatrixValueInCell(i - rowOffset, j - columnOffset) != -1 && board.getMatrixValueInCell(i - rowOffset, j - columnOffset)!= '@')
				{
					counter++;
					gotoxy(j, i);
					cout << ' ';
					board.setMatrixValueCell(i - rowOffset, j - columnOffset, -1);
				}
			}
		}
	}
	gotoxy(col, row);
	cout << ' ';
	return counter;
}
void Bomb::goDown(const GameBoard& board,int& moveCounter)
{
	moveCounter = 0;
	int y = body.getYCoordinate();

	y++;

	erase();
	body.setYCoordinate(y);
	draw();
}

