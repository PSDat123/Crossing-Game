#pragma once
#include "Console.h"

class Map {
public:
	Map(int, int);
	~Map();

	void drawMap();
private:
	int width, height;
};