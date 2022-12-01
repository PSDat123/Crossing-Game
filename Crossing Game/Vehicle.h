#pragma once
#include "Console.h"
#include "Macro.h"

using namespace std;

class Vehicle {
public:
	Vehicle();
	Vehicle(float x, float y, SHORT min_x, SHORT max_x, vector<wstring> sprite, DIRECTION dir=DIRECTION::RIGHT);
	virtual ~Vehicle();
	void setVX(SHORT);
	void setVY(SHORT);

	int getVX();
	int getVY();
	int getLength();
	int getHeight();
	bool getState();
	void update();
	void draw(Console*);
protected:
	vector<wstring> sprite;
	float x, y, speed;
	SHORT max_x, min_x;
	int prev_x, length;
	DIRECTION dir;
	bool state = true;
};
