#pragma once
#include "Vehicle.h"

class Bike : public Vehicle {
public:
	static map<DIRECTION, vector<vector<wstring>>> spriteSheet;
	Bike(int x, int y, int max_x, int min_x = 0, DIRECTION dir = DIRECTION::RIGHT);
	~Bike();
	string className();
private:
	bool wrapAround = true;
};