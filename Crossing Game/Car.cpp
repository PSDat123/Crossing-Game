#include "Car.h"

string Car::className() {
	return "Car";
}

map<DIRECTION, vector<vector<wstring>>> Car::spriteSheet= {
{	
	DIRECTION::RIGHT,
	{
		{
			L"    _____      ",
			L" __/__│__\\____ ",
			L"|     |      (|",
			L"=(O)══════(O)═╛"
		},
		{
			L" _.-.___\\__    ",
			L"|)         `―. ",
			L"╘═(O)════(O)══'"
		},
		{
			L"          __       ",
			L"H________H__]\\____.",
			L"|________|'    _ _:",
			L"'  /(_)   \"\"\"\"/(_) "
		}
	}
},
{
	DIRECTION::LEFT,
	{
		{
			L"      _____    ",
			L" ____/__│__\\__ ",
			L"│)      |     │",
			L"╘(O)══════(O)═="
		},
		{
			L"    __/____.-._ ",
			L" .-'          (|",
			L"'══(O)════(O)══╛"
		},
		{	
			L"      ____        ",
			L" ____//_]|________",
			L"(o _ |  -|   _  o|",
			L" `(_)-------(_)--'"
		}, 
		{
			L"      _____________",
			L" ____//__][__][___|",
			L"(o  _|  -|     _ o|",
			L" `-(_)--------(_)-'"
		}
	}
}
};


Car::Car(int x, int y, int max_x, int min_x, DIRECTION dir) : 
	Vehicle((float)x, (float)y, min_x, max_x, spriteSheet[dir][rand() % spriteSheet[dir].size()], dir) {}

Car::~Car() {}