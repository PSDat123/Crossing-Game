#include "Car.h"

string Car::className() {
	return "Car";
}

map<DIRECTION, vector<vector<wstring>>> Car::spriteSheet= {
{	
	DIRECTION::RIGHT,
	{
		{
			L"  _______     ",
			L" /|_||_\\ \\__  ",
			L"|)         (\\ ",
			L"=`(o)---(o)-J "
		},
		{
			L" _.-.___\\__    ",
			L"|)        _`-. ",
			L"'-(o)----(o)--`"
		},
		{
			L"  __~@",
			L"  _`\\<,_",
			L"(*)/ (*)"
		}
	}
},
{
	DIRECTION::LEFT,
	{
		{
			L"     ________  ",
			L" ___/__||____\\ ",
			L"/)     ||   (| ",
			L"'-(o)----(o)-= "
		},
		{
			L"      _____    ",
			L" ____/__|__\\__ ",
			L"|)     |      |",
			L"`(o)------(o)-="
		}
	}
}
};


Car::Car(int x, int y, int max_x, int min_x, DIRECTION dir) {
	sprite = spriteSheet[dir][rand() % spriteSheet[dir].size()];
	speed = 1;
	length = 0;
	for (wstring& s : sprite) {
		if ((int)s.size() > length) {
			length = (int)s.size();
		}
	}

	if (x > -1) {
		this->x = x;
		this->y = y;
		prev_x = x;
		prev_y = y;
	}
	else {
		this->x = min_x-length;
		this->y = y;
		prev_x = min_x -length;
		prev_y = y;
	}
	this->max_x = max_x;
	this->min_x = min_x;
	this->dir = dir;
	if (this->x + length < this->min_x || this->x > this->max_x) state = false;
}

Car::~Car() {}