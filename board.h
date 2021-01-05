#pragma once
#include "pch.h"
#include "values.h"
#include "ant.h"


class Board {
private:
	int width,
		heigth,
		loops,
		delay;

	char *board;
	Ant *ant;

public:
	Board(int, int);
	~Board();

	void draw() const;
	void fill(char=BLACK);
	void flipTile(int, int);

	int getLoops() const;
	int getHeigth() const;

	void loop();
};