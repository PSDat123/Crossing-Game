#include "Vehicle.h"

Vehicle::Vehicle(int x, int y) {
	this->x = x;
	this->y = y;
	this->prev_x = x;
	this->prev_y = y;
	GetConsoleSize(this->max_x, this->max_y);
}

void Vehicle::draw() {
	GotoXY(this->prev_x, this->prev_y);
	cout << "       ";
	GotoXY(this->prev_x, this->prev_y + 1);
	cout << "       ";
	GotoXY(this->prev_x, this->prev_y + 2);
	cout << "       ";
	GotoXY(this->prev_x, this->prev_y + 3);
	cout << "       ";

	GotoXY(this->x, this->y);
	cout << "  _______";
	GotoXY(this->x, this->y + 1);
	cout << " /|_||_\\ \\__";
	GotoXY(this->x, this->y + 2);
	cout << "|)         (\\";
	GotoXY(this->x, this->y + 3);
	cout << "=`(o)---(o)-J";
}

void Vehicle::move(DIRECTION dir) {
	switch (dir){
	case DIRECTION::UP:
		break;
	case DIRECTION::DOWN:
		break;
	case DIRECTION::LEFT:
		this->prev_x = this->x;
		if (this->x <= 0) this->x = this->max_x;
		else this->x--;
		break;
	case DIRECTION::RIGHT:
		this->prev_x = this->x;
		if (this->x >= this->max_x) this->x = 0;
		else this->x++;
		break;
	default:
		break;
	}
}

int Vehicle::getVX() {
	return this->x;
}

int Vehicle::getVY() {
	return this->y;
}

Car::Car(int x, int y) : Vehicle(x,y) {}

Truck::Truck(int x, int y) : Vehicle(x,y) {}

Vehicle::~Vehicle(){}