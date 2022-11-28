#pragma once
#include "Macro.h"
#include "Console.h"
#include "Car.h"
#include "Truck.h"

class Lane {
public:
	Lane();
	Lane(SHORT x, SHORT y, SHORT width, SHORT height, DIRECTION dir=DIRECTION::RIGHT);
	//void update();
	void drawLane(Console* console);
	void updateVehicles();
	void drawVehicles(Console* console);
private:
	deque<Vehicle> qVehicle;
	SHORT x, y, width, height;
	DIRECTION dir;
	int frameSinceLastVehicle = 0;
};