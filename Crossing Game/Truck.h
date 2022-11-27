#pragma once
#include "Vehicle.h"

class Truck : public Vehicle {
public:
	static map<DIRECTION, vector<vector<wstring>>> spriteSheet;
	Truck(int x, int y, int max_x, DIRECTION dir=DIRECTION::RIGHT);
	string className();
};
