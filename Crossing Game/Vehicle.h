#pragma once
#include "Console.h"
#include "Macro.h"

using namespace std;

class Vehicle {
public:
	int getVX();
	int getVY();
	int getLength();
	bool getState();

	void move(DIRECTION);
	virtual void draw(Console*);
protected:
	vector<wstring> sprite;
	wstring empty;
	SHORT x, y, prev_x, prev_y, max_x, max_y;
	int speed, length;
	bool state = true;
};

class Car : public Vehicle {
public:
	static vector<vector<wstring>> spriteSheet;
	Car(int, int, int, int);
private:
	bool wrapAround = true;
};

class Truck : public Vehicle {
public:
	Truck(int, int);
};
