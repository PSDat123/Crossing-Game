#include "Bike.h"

string Bike::className() {
	return "Bike";
}

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


Bike::Bike(int x, int y, int max_x, int min_x, DIRECTION dir) : 
	Vehicle(x, y, min_x, max_x, spriteSheet[dir][rand() % spriteSheet[dir].size()],  dir) {}

Bike::~Bike() {}