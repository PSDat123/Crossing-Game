#include "Animal.h"

//Animal::Animal(int cur_x, int cur_y) {
//	this->x = cur_x;
//	this->y = cur_y;
//	this->prev_x = x;
//	this->prev_y = y;
//	GetConsoleSize(this->max_x, this->max_y);
//}
//
//int Animal::getAX() {
//	return this->x;
//}
//
//Bird::Bird(int x, int y) : Animal(x, y) {}
//
//Cow::Cow(int x, int y) : Animal(x, y) {}
//
//int Animal::getAY() {
//	return this->y;
//}
//
//void Animal::move(DIRECTION dir) {
//	switch (dir) {
//	case DIRECTION::UP:
//		break;
//	case DIRECTION::DOWN:
//		break;
//	case DIRECTION::LEFT:
//		this->prev_x = this->x;
//		if (this->x <= 0) this->x = this->max_x;
//		else this->x--;
//		break;
//	case DIRECTION::RIGHT:
//		this->prev_x = this->x;
//		if (this->x >= this->max_x) this->x = 0;
//		else this->x++;
//		break;
//	default:
//		break;
//	}
//}
//
//Animal::~Animal() {}