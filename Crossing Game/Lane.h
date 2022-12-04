#pragma once
#include "Macro.h"
#include "Console.h"
#include "Car.h"
#include "Truck.h"
#include "Bike.h"
#include "People.h"

class Lane {
public:
	Lane();
	Lane(SHORT x, SHORT y, SHORT width, SHORT height);

	void setDirection(DIRECTION);
	void setMinDist(SHORT);
	void setSpeed(float);
	void move(DIRECTION);
	
	SHORT getX();
	SHORT getY();
	SHORT getHeight();
	//void update();
	void drawLane(Console* console);
	void updateVehicles();
	void drawVehicles(Console* console);

	bool isInLane(People*);
	bool checkCollison(People* p);
private:
	Vehicle getRandomVehicle(int x, int y);
	deque<Vehicle> qVehicle;
	SHORT x, y, width, height;
	DIRECTION dir = DIRECTION::RIGHT;
	SHORT minDist = 10; // minimun distance between 2 vehichles
	float speed = 1;
	int frameSinceLastVehicle = 0;
};