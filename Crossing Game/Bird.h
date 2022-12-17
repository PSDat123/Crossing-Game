#pragma once
#include "Vehicle.h"

class Bird : public Vehicle {
public:
	static map<DIRECTION, vector<vector<wstring>>> spriteSheet;
	Bird(float x, float y, int min_x, int max_x, float speed, DIRECTION dir = DIRECTION::RIGHT);
	~Bird();
};