#include "People.h"

People::People(int cur_x, int cur_y) {
	this->x = cur_x;
	this->y = cur_y;
	this->state = false;
}

bool People::checkFrame(int a, int b) {
	return true;
}

bool People::isFinish() {
	return (x == 0);
}

int People::getX() {
	return this->x;
}

int People::getY() {
	return this->y;
}

People::~People() {}

bool People::isDead() {
	return state;
}