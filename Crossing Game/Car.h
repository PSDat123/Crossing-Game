#pragma once
#include "Vehicle.h"

class Car : public Vehicle {
public:
	static vector<vector<wstring>> spriteSheet;
	Car(int x, int y, int max_x, int max_y);
	~Car();
	string className();
private:
	bool wrapAround = true;
};