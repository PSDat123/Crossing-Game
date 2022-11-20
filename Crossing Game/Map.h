#pragma once
#include "Console.h"

class Map {
public:
	Map(int, int);
	~Map();

	friend void mapThread(Map*);
	void drawSideMenu();
	void drawLane(int);
	void drawMap();
private:
	int width, height;
	bool isRunning;
};