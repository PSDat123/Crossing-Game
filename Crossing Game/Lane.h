#pragma once
#include "Macro.h"
#include "Console.h"
#include "Car.h"
#include "Truck.h"
#include "Bike.h"

class Lane {
public:
	Lane();
	Lane(SHORT x, SHORT y, SHORT width, SHORT height, SHORT minDist, DIRECTION dir=DIRECTION::RIGHT);
	//void update();
	void drawLane(Console* console);
	void updateVehicles();
	void drawVehicles(Console* console);
private:
	deque<Vehicle> qVehicle;
	SHORT x, y, width, height;
	SHORT minDist; // minimun distance between 2 vehichles
	DIRECTION dir;
	int frameSinceLastVehicle = 0;
};