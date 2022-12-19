#pragma once
#include "Vehicle.h"

class Bike : public Vehicle {
public:
	static map<DIRECTION, vector<vector<wstring>>> spriteSheet;
	Bike(float x, float y, int min_x, int max_x, float speed, DIRECTION dir = DIRECTION::RIGHT);
	~Bike();
};