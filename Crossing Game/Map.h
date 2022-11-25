#pragma once
#include "Console.h"

class Map {
public:
	Map(int, int);
	~Map();
	void drawOutline(Console*);
private:
	int width, height;
};