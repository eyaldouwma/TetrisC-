#ifndef __THEGAME_H
#define __THEGAME_H

constexpr int MAX_SPEED = 1100;
constexpr int MIN_SPEED = 100;
constexpr int MID_SPEED = 550;
constexpr int numOfShapes = 7;

enum eBlock { SquareBlock, SnakeBlock, PlusBlock, ZshapeBlock, LshapeBlock, JokerBlock, BombBlock }; //in which shape random function chose

class theGame
{
private:
	int score;
	int pieces;
	int sleepMode; //how much time to wate between iterations due to the speed the user wants
public:

	theGame(int score = 0, int pieces = 0, int speed = 500) : score(score), pieces(pieces), sleepMode(speed) {}
	void run(bool& newGame);
	void printMenu() const;
	void drawBoard() const;
	void updatePieces(int pieces);
	void printGameOver() const;
	void updateScore(int score);
	void pauseGame(bool&exitGame, bool&newGame) const;
	void speedUp();
	void speedDown();
	void runWithMenuOptions();
	void initialUserInput(bool&quitGame);
	void startNewGameAfterGameOver(bool&newGame, bool&isGameOver);
	void checkGlobalKeyPressed(char key, bool& exitGame, bool& newGame);
	int getSleepMode() const;

};

#endif __THEGAME_H