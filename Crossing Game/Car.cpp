#include "Car.h"

string Car::className() {
	return "Car";
}

map<DIRECTION, vector<vector<wstring>>> Car::spriteSheet= {
{	
	DIRECTION::RIGHT,
	{
		{
			L"  _______",
			L" /|_||_\\ \\__",
			L"|)         (\\",
			L"=`(o)---(o)-J"
		},
		{
			L" _.-.___\\__",
			L"|)        _`-.",
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
			L"     ________ ",
			L" ___/__||____\\",
			L"/)     ||   (|",
			L"'-(o)----(o)-="
		},
		{
			L"      _____ ",
			L" ____/__|__\\__",
			L"|)     |      |",
			L"`(o)------(o)-="
		}
	}
}
};


Car::Car(int x, int y, int max_x, DIRECTION dir) {
	sprite = spriteSheet[dir][rand() % spriteSheet.size()];
	speed = 1;
	length = 0;
	for (wstring& s : sprite) {
		if ((int)s.size() > length) {
			length = s.size();
		}
	}

	if (x > -1) {
		this->x = x;
		this->y = y;
		prev_x = x;
		prev_y = y;
	}
	else {
		this->x = -length;
		this->y = y;
		prev_x = -length;
		prev_y = y;
	}
	this->max_x = max_x;
	if (this->x + length < 0 || this->x > this->max_x) state = false;
}

Car::~Car() {}