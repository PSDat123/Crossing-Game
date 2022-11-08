#pragma once
#include <iostream>
#include "Console.h"
#include "Macro.h"
using namespace std;

class Vehicle {
public:
	Vehicle(int x=0, int y=0);
	void move(DIRECTION);
	void draw();
private:
	int prev_x, prev_y;
	int max_x, max_y;
	int x, y;
};

class Car: public Vehicle {
public:
	Car();
private:
};
