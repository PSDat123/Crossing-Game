#include "Car.h"

string Car::className() {
	return "Car";
}

vector<vector<wstring>> Car::spriteSheet = {
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
};


Car::Car(int x, int y, int max_x, int max_y) {
	sprite = spriteSheet[rand() % spriteSheet.size()];
	speed = 1;
	empty = L"";
	length = 0;
	for (wstring& s : sprite) {
		if ((int)s.size() > length) {
			length = s.size();
		}
	}
	empty.append(speed, L' ');

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
	this->max_y = max_y;
	if (this->x + length < 0 || this->x > this->max_x) state = false;
}

Car::~Car() {}