#pragma once
#include "Vehicle.h"

class Truck : public Vehicle {
public:
	static map<DIRECTION, vector<vector<wstring>>> spriteSheet;
	Truck(float x, float y, int min_x, int max_x, float speed, DIRECTION dir = DIRECTION::RIGHT);
};
