#include "GameBoard.h"
#include "Shape.h"
#include "Gotoxy.h"

using namespace std;

//Shape::Shape(char symbol)
//{
//	this->symbol = symbol;
//}
char Shape::getSymbol() const
{
	return symbol;
}
const Point * Shape::getBody() const
{
	return body;
}
const Point& Shape::getPointFromBody(int i) const
{
	return body[i];
}
void Shape::draw() const
{
	for (int i = 0; i < 4; i++)
	{
		gotoxy(body[i].getXCoordinate(), body[i].getYCoordinate());
		cout << symbol;
	}
	
}
void Shape::erase() const
{
	for (int i = 0; i < 4; i++)
	{
		gotoxy(body[i].getXCoordinate(), body[i].getYCoordinate());
		cout << ' ';
	}
}
bool Shape::checkIfLRAvailable(char direction, const GameBoard& board) const
{
	switch (direction)
	{
	case Left:
		for (int i = 0; i < 4; i++)
		{
			if ((board.getMatrixValueInCell(body[i].getYCoordinate() - rowOffset, body[i].getXCoordinate() - 1 - columnOffset) != -1) || (body[i].getXCoordinate()==columnOffset))
			{
				return false;
			}
		}
		return true;

	case Right:
		for (int i = 0; i < 4; i++)
		{
			if ((board.getMatrixValueInCell(body[i].getYCoordinate() - rowOffset, body[i].getXCoordinate() +1 - columnOffset) != -1) || (body[i].getXCoordinate() == boardWidth))
			{
				return false;
			}
		}
		return true;
		
	default:
		return false;
	}
}

bool Shape::checkIfDownAvailable(const GameBoard& board) const
{
	int row, col;

	row = body[0].getYCoordinate();
	col = body[0].getXCoordinate();

	for(int i=0; i<4; i++)
	{
		if ((board.getMatrixValueInCell(body[i].getYCoordinate() + 1 -rowOffset, body[i].getXCoordinate() - columnOffset)!= -1) || (body[i].getYCoordinate()>17))
		{
			return false;
		}
	}
	return true;
}

void Shape::goDown(int& moveCounter)
{
	moveCounter = 0;
	int y;
	y = body[0].getYCoordinate();

	y++;

	erase();

	body[0].setYCoordinate(y);
	setBody(body[0]);

	draw();
}

void Shape::move(char direction, const GameBoard &board, int& moveCounter)
{
	switch (direction)
	{
	case Left: // left
	{
		if (checkIfLRAvailable(direction, board) == true)
		{
			moveCounter++;
			int x;
			x = body[0].getXCoordinate();

			x--;

			erase();

			body[0].setXCoordinate(x);
			setBody(body[0]);

			draw();
		}
		else
		{
			goDown(moveCounter);
		}
		break;
	}
	case Right: //right
	{
		if (checkIfLRAvailable(direction, board) == true)
		{
			moveCounter++;
			int x;
			x = body[0].getXCoordinate();

			x++;

			erase();

			body[0].setXCoordinate(x);
			setBody(body[0]);

			draw();
		}
		else
		{
			goDown(moveCounter);
		}
		break;
	}
	case Down: //straight down
	{
		int y;
		erase();
		while (checkIfDownAvailable(board))
		{
			y = body[0].getYCoordinate();
			y++;

			body[0].setYCoordinate(y);
			setBody(body[0]);
		}
		y--;
		body[0].setYCoordinate(y);
		setBody(body[0]);
		draw();
	}
	default: //down
	{
		goDown(moveCounter);
		break;
	}
	}
}