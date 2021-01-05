#include "pch.h"
#include "board.h"
#include <iostream>
#include "utils.h"

Board::Board(int w, int h) {
	width = w;
	heigth = h;
	ant = new Ant( (width/2), (heigth/2) );
	loops = 0;
	delay = 1000;
	 
	board = new char[width*heigth];
	fill();
}
Board::~Board() {
	delete[] board;
	delete[] ant;
}

void Board::fill(char filler) {
	for (int i = 0; i < heigth; i++) {
		for (int ii = 0; ii < width; ii++) {
			board[i*width + ii] = filler;
		}
	}
}

void Board::draw() const {
	for (int i = 0; i < heigth; i++) {
		for (int ii = 0; ii < width; ii++) {
			if ((i*width + ii) == ant->calcCoord(width))
				std::cout << ant->getLook();
			else
				std::cout << board[i*width + ii];	
		}
		std::cout << '\n';
	}
}

void Board::flipTile(int x, int y) {
	int coord = y * width + x;
	board[coord] == BLACK ? board[coord] = WHITE : board[coord] = BLACK;
}

int Board::getLoops() const {
	return loops;
}
int Board::getHeigth() const {
	return heigth;
}

void Board::loop() {
	if (ant->getX() >= width
		|| ant->getX() < 0
		|| ant->getY() >= heigth
		|| ant->getY() < 0) {

		setCursorPosition(0, heigth+1);
		std::cout << "Ant has fell off the board :(";
		exit(0);
	}


	char temp = board[ant->calcCoord(width)];
	flipTile(ant->getX(), ant->getY());

	setCursorPosition(ant->getX(), ant->getY());
	std::cout << board[ant->calcCoord(width)];

	
	ant->turnAndMove(temp);
	setCursorPosition(ant->getX(), ant->getY());
	std::cout << ant->getLook();
	loops++;
}