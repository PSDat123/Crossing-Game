#include "Truck.h"

string Truck::className() {
	return "Truck";
}

map<DIRECTION, vector<vector<wstring>>> Truck::spriteSheet = {
{
	DIRECTION::RIGHT,
	{
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
	}
},
{
	DIRECTION::LEFT,
	{
		{
			 L"   ________________________ "
			 L"  /   | |    |     |       |"
			 L" /----|_|----|-----|-------|"
			 L"/)  -        |     |      (|"
			 L"\'=====(O)===========(O)====\'"
		}
	}
}		 	 
};		 


Truck::Truck(int x, int y, int max_x, DIRECTION dir) {
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