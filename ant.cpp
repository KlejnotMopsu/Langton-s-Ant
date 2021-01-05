#include "pch.h"
#include "ant.h"
#include "values.h"
#include <cstdlib>
#include <iostream>

Ant::Ant(int x, int y) {
	X = x;
	Y = y;
	look = 'x';
}

int Ant::getX() const {
	return X;
}
int Ant::getY() const {
	return Y;
}

int Ant::calcCoord(int w) const{
	return Y * w + X;
}

char Ant::getLook() const {
	return look;
}

void Ant::move() {
	
	switch (look) {
	case 'x':
		look = UP;
		break;

	case char(UP):
		Y--;
		look = RIGHT;
		break;

	case char(DOWN) :
		Y++;
		look = LEFT;
		break;

	case char(LEFT) :
		X--;
		look = UP;
		break;

	case char(RIGHT):
		X++;
		look = DOWN;
		break;

	default:
		std::cout << "ANT : MOVING ERROR";
		std::exit(1);
	}
}

void Ant::moveDown() {
	Y++;
	look = DOWN;
}
void Ant::moveUp() {
	Y--;
	look = UP;
}
void Ant::moveLeft() {
	X--;
	look = LEFT;
}
void Ant::moveRight() {
	X++;
	look = RIGHT;
}

void Ant::turnAndMove(char tile) {
	if (look == 'x') {
		moveUp();
		return;
	}
		

	switch (tile) {
	case char(BLACK) :

		switch (look) {
		case char(UP) :
			moveRight();
			break;

		case char(DOWN) :
			moveLeft();
			break;

		case char(LEFT) :
			moveUp();
			break;

		case char(RIGHT) :
			moveDown();
			break;
		}


		break;

	case char(WHITE) :

		switch (look) {
		case char(UP) :
			moveLeft();
			break;

		case char(DOWN) :
			moveRight();
			break;

		case char(LEFT) :
			moveDown();
			break;

		case char(RIGHT) :
			moveUp();
			break;
		}

		break;

	default:
		std::cout << "ERROR: turnAndMove() default called";
		exit(2);
		break;
	}
}