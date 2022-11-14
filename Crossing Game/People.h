#pragma once
#include "Vehicle.h"
#include "Animal.h"

class People {
public:
	People(int, int);
	~People();

	int getX();
	int getY();

	void Up();
	void Left();
	void Right();
	void Down();

	bool isImpact(Vehicle*);
	bool isImpact(Animal*);
	bool isFinish();
	bool isDead();
private:
	int x, y;
	bool state; // dead/alive
	bool checkFrame(int,int);
};