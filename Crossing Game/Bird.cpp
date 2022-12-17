#include "Bird.h"

map<DIRECTION, vector<vector<wstring>>> Bird::spriteSheet = {
{
	DIRECTION::RIGHT,
	{
		{
			L"   .――.    ",
			L"\\\\_ - ,\\(O>",
			L" \\\\_'__ \\) "
		},
	}
},
{
	DIRECTION::LEFT,
	{
		{
			L"    ,――,   ",
		    L"<O)/ ,- _//",
			L" (/ __'_// "
		},
	}
}
};

Bird::Bird(float x, float y, int min_x, int max_x, float speed, DIRECTION dir) :
	Vehicle(x, y, min_x, max_x, speed, spriteSheet[dir][rand() % spriteSheet[dir].size()], dir) {}

Bird::~Bird() {}