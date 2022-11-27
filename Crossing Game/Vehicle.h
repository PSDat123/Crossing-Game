#pragma once
#include "Console.h"
#include "Macro.h"

using namespace std;

class Vehicle {
public:
	virtual ~Vehicle();
	int getVX();
	int getVY();
	int getLength();
	bool getState();

	void move(DIRECTION);

	virtual void draw(Console*);
protected:
	vector<wstring> sprite;
	SHORT x, y, prev_x, prev_y, max_x;
	int speed, length;
	bool state = true;
};
