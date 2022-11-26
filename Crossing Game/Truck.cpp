#include "Truck.h"

string Truck::className() {
	return "Truck";
}

vector<vector<wstring>> Truck::spriteSheet = {
	{
		L" _______________  _____",
		L"|               ||___|_\\",
		L"|===============|| -    |",
		L"|               ||     (|",
		L"'==(o)====(o)=======(o)=J "
	},
	{
		L"                  /\\\\      _____   ",
		L"    ,------      /  \\\\____/__|__\\_ ",
		L" ,--'---:---`--,/   |)       |   (|",
		L"==(o)-----(o)==J    `(o)=======(o)J"
	}
};


Truck::Truck(int x, int y, int max_x, int max_y) {
	sprite = spriteSheet[rand() % spriteSheet.size()];
	speed = 1;
	empty = L"";
	length = 0;
	for (wstring& s : sprite) {
		if ((int)s.size() > length) {
			length = (int)s.size();
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