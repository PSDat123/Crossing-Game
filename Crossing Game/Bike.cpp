#include "Bike.h"

map<DIRECTION, vector<vector<wstring>>> Bike::spriteSheet = {
{
	DIRECTION::RIGHT,
	{
		{
			L"    O_,   ",
			L"=='\\|_ͻ\\-.",
			L" (O)═══(O)",
		},
		{
			L"  __~@   ",
			L"  _`\\<,_ ",
			L"(*)/ (*) "
		}
	}
},
{
	DIRECTION::LEFT,
	{
		{
			L"   ,_O    ",
			L".-/c_|/'==",
			L"(O)═══(O) ",
		},
		{
			L"  o__   ",
			L" _.>/ _ ",
			L"(_) \\(_)"
		}
	}
}
};


Bike::Bike(float x, float y, int min_x, int max_x, float speed, DIRECTION dir) : 
	Vehicle(x, y, min_x, max_x, speed, spriteSheet[dir][rand() % spriteSheet[dir].size()],  dir) {}

Bike::~Bike() {}