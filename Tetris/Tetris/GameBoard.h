#ifndef __GAMEBOARD_H
#define __GAMEBOARD_H

#include "Point.h"
#include "theGame.h"
#include "Utils.h"

enum eRowResult {NoRow, CompleteRow, CompleteRowWithJoker};

class GameBoard
{
private:
	char matrix[boardLength][boardWidth];
public:
	GameBoard();

	void setMatrixValueCell(int i, int j, char value);

	bool checkAndUpdateBoard(int& score);
	eRowResult checkRow(int row);

	void fallAllPieces(int row);

	char getMatrixValueInCell(int i, int j) const;

	void updateShape(const Point body[], char symbol);
	void updateShape(const Point body, char symbol);
	void updateJoker(const Point& joker, char symbol);

	void eraseRow(int i);

	void printAllValues() const;

	bool checkIfGameIsOver(eBlock shape);

};

#endif __GAMEBOARD_H
