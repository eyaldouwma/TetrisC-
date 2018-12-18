#include "SpecialShape.h"
#include "Gotoxy.h"
#include "GameBoard.h"


using namespace std;

void SpecialShape::setBody(const Point& body)
{
	this->body = body;
}

const Point& SpecialShape::getBody() const
{
	return body;
}

void SpecialShape::draw() const
{
	int x, y;

	x = body.getXCoordinate();
	y = body.getYCoordinate();

	gotoxy(x, y);
	cout << symbol;
}

void SpecialShape::erase() const // After the bomb explodes, we erase it form the board
{
	int x, y;

	x = body.getXCoordinate();
	y = body.getYCoordinate();

	gotoxy(x, y);
	cout << ' ';
}

char SpecialShape::getSymbol() const
{
	return symbol;
}