#include "People.h"

People::People(int cur_x, int cur_y) {
	this->x = cur_x;
	this->y = cur_y;
	this->state = false;
}

bool People::checkFrame(int a, int b) {
	return ((0 <= a && a < 42) && (25 <= b && b < 135));
}

void People::Up() {

}

void People::Down() {

}

void People::Left() {

}

void People::Right() {

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