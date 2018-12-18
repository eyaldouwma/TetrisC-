#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include "Joker.h"
#include "Square.h"
#include "Snake.h"
#include "Plus.h"
#include "Zshape.h"
#include "Lshape.h"
#include "theGame.h" 
#include "Bomb.h"
#include "Gotoxy.h"
#include "Utils.h"
#include <typeinfo>

using namespace std;

void theGame::run(bool& newGame)
{
		GameBoard board;
		bool exitGame = false;
		char keyPressed;
		int whichObject, moveCounter;
		bool exploded = false;
		
		score = 0;
		pieces = 0;

		updateScore(score);

		while (exitGame == false)
		{
			Shape* pShape = nullptr;
			SpecialShape *pSpecShape = nullptr;

			whichObject = rand() % numOfShapes;
			updatePieces(pieces);
			moveCounter = 0;

			if (board.checkIfGameIsOver((eBlock)whichObject) == true)
			{
				exitGame = true;
			}
			else
			{
				if (((eBlock)whichObject >= SquareBlock) && ((eBlock)whichObject <= LshapeBlock))//Regular Shapes Scenario
				{
					if ((eBlock)whichObject == SquareBlock)
					{
						pShape = new Square;
						pShape->setBody();
					}
					else if ((eBlock)whichObject == SnakeBlock)
					{
						pShape = new Snake;
						pShape->setBody();
					}
					else if ((eBlock)whichObject == PlusBlock)
					{
						pShape = new Plus;
						pShape->setBody();
					}
					else if ((eBlock)whichObject == ZshapeBlock)
					{
						pShape = new Zshape;
						pShape->setBody();
					}
					else if ((eBlock)whichObject == LshapeBlock)
					{
						pShape = new Lshape;
						pShape->setBody({6,5});
					}
					pShape->draw();
					while (pShape->checkIfDownAvailable(board))
					{
						Sleep(sleepMode);
						if (moveCounter < 3)
						{
							if (_kbhit()) //if there is an input
							{
								keyPressed = _getch();
								checkGlobalKeyPressed(keyPressed, exitGame, newGame);
								if (exitGame == true || newGame == true)
								{
									break;
								}
								if (keyPressed == Rotate) //rotate was pressed
								{
									pShape->rotate(board, moveCounter);
								}
								else
								{
									pShape->move(keyPressed, board, moveCounter);
								}
							}
							else //if there was no input specified, just go down
							{
								pShape->goDown(moveCounter);
							}
						}
						else //if the user pressed 3 times left & right on the same height level, we force the object to go down
						{
							pShape->goDown(moveCounter);
						}
						FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
					}
					board.updateShape(pShape->getBody(), pShape->getSymbol());
				}
				else //Special Shapes Scenario - Bomb / Joker
				{
					if ((eBlock)whichObject == JokerBlock)
					{
						pSpecShape = new Joker;
						pSpecShape->setBody();
					}
					else if ((eBlock)whichObject == BombBlock)
					{
						pSpecShape = new Bomb;
						pSpecShape->setBody();
					}
					exploded = false;
					pSpecShape->draw();
					while (pSpecShape->checkIfDownAvailable(board))
					{
						Sleep(sleepMode);
						if (moveCounter < 3)
						{
							if (_kbhit())
							{
								keyPressed = _getch();
								checkGlobalKeyPressed(keyPressed, exitGame, newGame);
								if (exitGame == true || newGame == true)
								{
									break;
								}
								if (keyPressed == Stop && typeid(*pSpecShape) == typeid(Joker))
								{
									break;
								}
								pSpecShape->move(keyPressed,board,moveCounter,exploded);
								if (exploded == true)
								{
									score = score - (50 * ((Bomb*)pSpecShape)->explode(board));
									updateScore(score);
									break;
								}
							}
							else
							{
								pSpecShape->goDown(board, moveCounter);
							}
						}
						else
						{
							pSpecShape->goDown(board, moveCounter);
						}
						FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
					}
					if (typeid(*pSpecShape) == typeid(Joker))
					{
						board.updateJoker(pSpecShape->getBody(), pSpecShape->getSymbol());
					}
				}
				if (exitGame == false)
				{
					pieces++;
					if ((eBlock)whichObject != BombBlock)
					{
						if (board.checkAndUpdateBoard(score) == true)
						{
							updateScore(score);
						}
					}
					else
					{
						if (exploded == false)
						{
							pieces++;
							score = score - (50 * ((Bomb*)pSpecShape)->explode(board));
							updateScore(score);
						}
					}
				}
			}
		}
		//gotoxy(0, 20);
		//board.printAllValues();
}
void theGame::drawBoard() const
{
	int y, x;
	gotoxy(0, 0);
	cout << "Score: " << endl << "Pieces: " << endl;

	for (x = 0; x < 12; x++) //ceiling
	{
		gotoxy(x, 3);
		cout << "~";
	}
	
	for (y = 4; y < 19; y++) //left wall
	{
		gotoxy(0, y);
		cout << "|";
	}

	for (y = 4; y < 19; y++) //right wall
	{
		gotoxy(11, y);
		cout << "|";
	}
	for (x = 0; x < 12;x++) //floor
	{
		gotoxy(x, 19);
		cout << "~";
	}
}

void theGame::updatePieces(int pieces)
{
	gotoxy(8, 1);
	for (int i = 0; i < 12; i++)
	{
		cout << ' ';
	}
	gotoxy(8, 1);
	cout << pieces;
}
void theGame::updateScore(int score)
{
	gotoxy(7, 0);
	for (int i = 0; i < 12; i++)
	{
		cout << ' ';
	}
	gotoxy(7, 0);
	cout << score;
}
void theGame::printGameOver() const
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hstdout, &csbi);

	SetConsoleTextAttribute(hstdout, FOREGROUND_INTENSITY | BACKGROUND_BLUE);

	gotoxy(1, 10);

	cout << "GAME OVER" << endl;

	SetConsoleTextAttribute(hstdout, csbi.wAttributes);

	gotoxy(0, 21);
}
void theGame::printMenu() const
{
	//prints the menu
	gotoxy(20, 0);
	cout << "For new game press:"; 
	gotoxy(54, 0);
	cout << "<1>" << endl;
	gotoxy(20, 1);
	cout << "For Pause / Resume press:";
	gotoxy(54, 1);
	cout << "<2>" << endl;
	gotoxy(20, 2);
	cout << "To Increase the game speed press: <3>" << endl;
	gotoxy(20, 3);
	cout << "To Decrease the game speed press: <4>" << endl;
	gotoxy(20, 4);
	cout << "To Quit the game press:";
	gotoxy(54, 4);
	cout << "<9>";
	gotoxy(30, 10);
	cout << "--------------";
	gotoxy(30, 11);
	cout << "| SPEED: " << MID_SPEED << " |";
	gotoxy(30, 12);
	cout << "--------------";
}
void theGame::pauseGame(bool &exitGame, bool& newGame) const
{
		char keyPressed = 0;
		while (keyPressed != PauseResume)
		{
			if (_kbhit())
			{
				keyPressed = _getch();
				if (keyPressed == New)
				{
					newGame = true;
					exitGame = true;
					break;
				}
				else if (keyPressed == Quit)
				{
					exitGame = true;
					break;
				}
			}
		}
}
void theGame::runWithMenuOptions()
{
	bool quitGame = false;
	bool newGame = true;
	bool isGameOver = false;

	printMenu();
	drawBoard();

	initialUserInput(quitGame); //the user can choose to start the game, or quit before starting

	if (quitGame == false)//if the user pressed '1' for playing the game
	{
		while (isGameOver == false)//after the game is over, the user can decide to play again
		{
			while (newGame == true)//if the user entered '1' while in game play, the game will restart
			{
				newGame = false;
				run(newGame);
			}

			printGameOver();
			startNewGameAfterGameOver(newGame, isGameOver);//present the user the option to renew the game after the game is over
		}
	}
	else //the user decided to quit before even starting the game pressing '9'
	{
		printGameOver();
	}
	cout << endl;
}
void theGame::speedUp()
{
	if (sleepMode != MIN_SPEED)
	{
		sleepMode -= 50;
		gotoxy(39, 11);
		cout << "    ";
		gotoxy(39, 11);
		cout << (MAX_SPEED-sleepMode); // the more the sleep is long, the speed we show the user is lower
	}

}
void theGame::speedDown()
{
	if (sleepMode != MAX_SPEED)
	{
		sleepMode += 50;
		gotoxy(39, 11);
		cout << "    ";
		gotoxy(39, 11);
		cout << (MAX_SPEED-sleepMode); // the more the sleep is short, the speed we show the user is higher
	}
}
int theGame::getSleepMode() const
{
	return sleepMode;
}
void theGame::initialUserInput(bool&quitGame)
{
	char key = 0;
	while (key != New)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == Quit)
			{
				quitGame = true;
				key = New;
			}
		}
	}
}
void theGame::startNewGameAfterGameOver(bool&newGame, bool&isGameOver)
{
	cout << "Press 1 for new game, 9 to exit";
	char key = 0;

	while (key != New && key != Quit)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == Quit)
			{
				isGameOver = true;
			}
			if (key == New)
			{
				newGame = true;
			}
		}
	}
	gotoxy(0, 21);
	for (int i = 0; i <= 30; i++)
	{
		cout << ' ';
	}
}
void theGame::checkGlobalKeyPressed(char key, bool& exitGame, bool& newGame)
{
	if (key == Quit)
	{
		exitGame = true;
	}
	else if (key == New)
	{
		newGame = true;
		exitGame = true;
	}
	else if (key == PauseResume)
	{
		pauseGame(exitGame, newGame);
	}
	else if (key == IncreaseSpeed)
	{
		speedUp();
	}
	else if (key == DecreaseSpeed)
	{
		speedDown();
	}
}
