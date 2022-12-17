#include "Car.h"

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


Car::Car(float x, float y, int min_x, int max_x, float speed, DIRECTION dir) :
	Vehicle(x, y, min_x, max_x, speed, spriteSheet[dir][rand() % spriteSheet[dir].size()], dir) {}

Car::~Car() {}