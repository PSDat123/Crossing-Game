#pragma once
#include "Console.h"
#include "Macro.h"

class Animal {
public:
	Animal(int, int);
	~Animal();

	int getAX();
	int getAY();

	void move(DIRECTION);
	void draw();
	virtual void playSound();
	virtual int type() = 0; //0 for bird 1 for cow
private:
	string texture[6];
	int x, y;
	int prev_x, prev_y;
	int max_x, max_y;
};

class Bird : public Animal {
public:
	Bird(int, int);
	~Bird();
	void playSound();
	int type();
};

class Cow : public Animal {
public:
	Cow(int, int);
	~Cow();
	void playSound();
	int type();
};