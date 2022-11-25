#pragma once
#include "Vehicle.h"

class Truck : public Vehicle {
public:
	static vector<vector<wstring>> spriteSheet;
	Truck(int x, int y, int max_x, int max_y);
	string className();
};
