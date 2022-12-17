#pragma once
#include "Console.h"
#include "Car.h"
#include "Truck.h"
#include "Bike.h"
#include "Bird.h"
#include "People.h"

class Lane {
public:
	Lane();
	Lane(SHORT x, SHORT y, SHORT width, SHORT height);

	void setDirection(DIRECTION);
	void setMinDist(SHORT);
	void setSpeed(float);
	void increaseSpeed(float);
	void move(DIRECTION);
	
	SHORT getX();
	SHORT getY();
	SHORT getHeight();
	void drawLane(Console* console);
	void updateVehicles(Console* console);
	void updateTraffic();
	void drawVehicles(Console* console);
	void drawTrafficLight(Console* console);
	void drawAll(Console* console);
	bool isInLane(People*);
	bool checkCollison(People* p);
private:
	Vehicle getRandomVehicle(int x, int y);
	deque<Vehicle> qVehicle;
	SHORT x, y, width, height;
	DIRECTION dir = DIRECTION::RIGHT;
	SHORT minDist = 10; // minimun distance between 2 vehichles
	float speed = 1;
	TRAFFIC trafficState = TRAFFIC::GREEN;
	float defaultCD, CD;
	chrono::system_clock::time_point timeStamp;
};