#include <iostream>
#include <Windows.h>
#include "GameBoard.h"
#include "Gotoxy.h"
#include "Shape.h"


using namespace std;

GameBoard::GameBoard() //constructor
{
	int i, j;

	for (i = 0; i < boardLength; i++)
	{
		for (j = 0; j < boardWidth; j++)
		{
			matrix[i][j] = -1;

			gotoxy(j + columnOffset, i + rowOffset); //erase the board visually
			cout << ' ';
		}
	}
}
void GameBoard::setMatrixValueCell(int i, int j, char value) // -1 for an empty cell, a shape's symbol otherwise
{
	matrix[i][j] = value;
}
char GameBoard::getMatrixValueInCell(int i, int j) const // is this cell full? with what? if it is empty, the value is -1
{
	return matrix[i][j];
}
void GameBoard::eraseRow(int i)
{
	int j;

	for (j = 0; j < boardWidth; j++)
	{
		gotoxy(j + columnOffset, i + rowOffset);
		cout << ' ';
		matrix[i][j] = -1;
	}
}
void GameBoard::updateShape(const Point body[], char symbol)
{
	int col, row;

	for (int i = 0; i < ShapeSize; i++)
	{
		col = body[i].getXCoordinate();
		row = body[i].getYCoordinate();

		matrix[row - rowOffset][col - columnOffset] = symbol;
	}
}
void GameBoard::updateShape(const Point body, char symbol)
{
	int col, row;

	col = body.getXCoordinate();
	row = body.getYCoordinate();

	matrix[row - rowOffset][col - columnOffset] = symbol;

}
void GameBoard::printAllValues() const // print the new picture after we erased a full row. (all the objects above it got down)
{
	int i, j;

	for (i = 0; i < boardLength; i++)
	{
		for (j = 0; j < boardWidth; j++)
		{
			cout << (int)matrix[i][j] << ' ';
		}
		cout << endl;
	}
}
bool GameBoard::checkAndUpdateBoard(int& score) // check if there is a full row in the board 
{
	int i;

	eRowResult checkRowVar;
	
	bool scoreUpdated = false;

	for (i = 0; i < boardLength; i++)
	{
		checkRowVar = checkRow(i);
		if ((checkRowVar == CompleteRow) || (checkRowVar == CompleteRowWithJoker)) //check if there is a whole row without '-1'
		{
			Sleep(100);
			eraseRow(i); //erase the row, visualy and updates the matrix with '-1'
			fallAllPieces(i); //update the pieces accordingly
			if (checkRowVar == CompleteRowWithJoker)
			{
				score = score + 50;
			}
			else
			{
				score = score + 100; // updates the score
			}
			scoreUpdated = true;
		}
	}

	return scoreUpdated;
	
}
eRowResult GameBoard::checkRow(int i)
{
	int j;
	bool joker = false;

	for (j = 0; j < boardWidth; j++)
	{
		if (matrix[i][j] == -1)
		{
			return NoRow;
		}
		else if (matrix[i][j] == '$')
		{
			joker = true;
		}
	}
	if (joker == true)
	{
		return CompleteRowWithJoker;
	}
	else
	{
		return CompleteRow;
	}
	
}
void GameBoard::fallAllPieces(int row)
{
	int i, j;
	for (i = row - 1; i >= 0; i--)
	{
		for (j = 0; j < boardWidth; j++)
		{
			if (matrix[i][j] != -1)
			{
				gotoxy(j + columnOffset, i + rowOffset);
				cout << ' ';
				matrix[i + 1][j] = matrix[i][j];
				gotoxy(j + 1, i + 5);
				cout << matrix[i][j];
				matrix[i][j] = -1;
			}
		}
	}
}
void GameBoard::updateJoker(const Point& joker, char symbol) // fill the board with Joker's symbol in the current place
{
	int col, row;

	col = joker.getXCoordinate();
	row = joker.getYCoordinate();

	matrix[row - rowOffset][col - columnOffset] = symbol;
}

bool GameBoard::checkIfGameIsOver(eBlock shape) // if there is no room for a new shape
{
	int row = 4, col = 5;
	switch (shape)
	{
	case(SquareBlock):
	{
		for (row = 4; row < 6; row++)
		{
			for (col = 4; col < 6; col++)
			{
				if (matrix[row - rowOffset][col - columnOffset] != -1)
				{
					if (row == 5)
					{
						for (int i = 4; i < 6; i++)
						{
							gotoxy(i, 4);
							cout << "O";
						}
					}
					return true;
				}
			}
		}
		return false;
		break;
	}
	case(SnakeBlock):
	{
		for (col = 5; col < 9; col++)
		{
			if (matrix[row - rowOffset][col - columnOffset] != -1)
			{
				return true;
			}
		}
		return false;
		break;
	}
	case(BombBlock):
	{
		if (matrix[row - rowOffset][col - columnOffset] != -1)
			return true;
		return false;
		break;
	}
	case(ZshapeBlock):
	{
		col = row = 4;
		if (matrix[row - rowOffset][col - columnOffset] != -1 || matrix[row - rowOffset][col + 1 - columnOffset] != -1)
		{
			return true;
		} 
		else if (matrix[row + 1 - rowOffset][col + 1 - columnOffset] != -1 || matrix[row + 1 - rowOffset][col + 2 - columnOffset] != -1)
		{
			gotoxy(5, 4);
			cout << 'O';
			gotoxy(6, 4);
			cout << 'O';
			return true;
		}
		return false;
	}
	case(PlusBlock):
	{
		col = row = 4;
		if (matrix[row - rowOffset][col - columnOffset] != -1)
		{
			return true;
		}
		else if (matrix[row+1-rowOffset][col-1-columnOffset]!=-1 || matrix[row+1-rowOffset][col-columnOffset]!=-1 || matrix[row+1-rowOffset][col+1-columnOffset]!=-1)
		{
			for (int i = col - 1; i < 6; i++)
			{
				gotoxy(i, 4);
				cout << 'O';
			}
			return true;
		}
		return false;
	}
	case(LshapeBlock):
	{
		col = 6;
		row = 5;

		if (matrix[row - 1 - rowOffset][col - columnOffset] != -1 || matrix[row - 1 - rowOffset][col - 1 - columnOffset] != -1 || matrix[row - 1 - rowOffset][col - 2 - columnOffset] != -1)
		{
			return true;
		}
		else if (matrix[row - rowOffset][col - columnOffset] != -1)
		{
			gotoxy(6, 4);
			cout << 'O';
			return true;
		}
		return false;
	}
	default:
	{
		return false;
		break;
	}
	}
}
