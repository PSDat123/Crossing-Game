#pragma once
#include "Console.h"
#include "Macro.h"

class Vehicle {
public:
	Vehicle(int x = 0, int y = 0);
	~Vehicle();

	int getVX();
	int getVY();

	void move(DIRECTION);
	void draw();
private:
	int prev_x, prev_y;
	int max_x, max_y;
	int x, y;
};

class Car : public Vehicle {
public:
	Car(int, int);
};

class Truck : public Vehicle {
public:
	Truck(int, int);
};
