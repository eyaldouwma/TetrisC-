#ifndef __POINT_H
#define __POINT_H

class Point //uses to move from point to point on the game board & whole console
{

private:

	int x;
	int y;

public:

	Point(int x=0, int y=0);
	int getXCoordinate() const { return x; } 
	void setXCoordinate(int x);

	int getYCoordinate() const { return y; }
	void setYCoordinate(int y);

	void setXYCoordinate(int x, int y);


};

#endif __POINT_H
