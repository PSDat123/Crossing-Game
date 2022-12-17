#pragma once
#include "Vehicle.h"

class Car : public Vehicle {
public:
	static map<DIRECTION, vector<vector<wstring>>> spriteSheet;
	Car(float x, float y, int min_x, int max_x, float speed, DIRECTION dir = DIRECTION::RIGHT);
	~Car();
};