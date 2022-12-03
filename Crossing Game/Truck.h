#pragma once
#include "Vehicle.h"

class Truck : public Vehicle {
public:
	static map<DIRECTION, vector<vector<wstring>>> spriteSheet;
	Truck(int x, int y, int min_x, int max_x, float speed, DIRECTION dir = DIRECTION::RIGHT);
	string className();
};
