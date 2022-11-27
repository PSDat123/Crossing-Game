#pragma once
#include "Vehicle.h"

class Car : public Vehicle {
public:
	static map<DIRECTION, vector<vector<wstring>>> spriteSheet;
	Car(int x, int y, int max_x, DIRECTION dir=DIRECTION::RIGHT);
	~Car();
	string className();
private:
	bool wrapAround = true;
};