#pragma once
#include "Macro.h"
#include "People.h"

using namespace std;

class Vehicle {
public:
	Vehicle();
	Vehicle(float x, float y,
	 				SHORT min_x, SHORT max_x,
	  			float speed, vector<wstring> sprite,
					DIRECTION dir = DIRECTION::RIGHT);
	virtual ~Vehicle();
	void setVX(SHORT);
	void setVY(SHORT);

	int getVX();
	int getVY();
	int getLength();
	int getHeight();
	bool getState();
	void update(float mult = 1);
	void clear(Console*);
	void draw(Console*);
	bool checkCollision(People*);
protected:
	vector<wstring> sprite;
	float x, y, speed;
	SHORT max_x, min_x;
	int prev_x, length, height;
	DIRECTION dir;
	bool state = true;
};