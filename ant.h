#pragma once
#include "pch.h"

class Ant {
private:
	int X, Y;
	char look;

public:
	Ant(int, int);

	int getX() const;
	int getY() const;
	int calcCoord(int) const;
	char getLook() const;

	void move();
	void moveDown();
	void moveUp();
	void moveLeft();
	void moveRight();

	void turnAndMove(char);
};