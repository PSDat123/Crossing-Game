#pragma once
#include "Console.h"
#include "Macro.h"

class Vehicle {
public:
	Vehicle(int x = 0, int y = 0);
	~Vehicle();

	int getVX();
	int getVY();
	int getLength();
	bool getState();

	void move(DIRECTION);
	virtual void draw();
protected:
	vector<wstring> sprite;
	wstring empty;
	int prev_x, prev_y;
	int max_x, max_y;
	int x, y;
	int speed, length;
	bool state = true;
};

class Car : public Vehicle {
public:
	static vector<vector<wstring>> spriteSheet;
	Car(int, int, int, int);
	void draw();
private:
	bool wrapAround = true;
};

class Truck : public Vehicle {
public:
	Truck(int, int);
};
