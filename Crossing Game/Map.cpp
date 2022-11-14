#include "Map.h"

Map::Map(int w, int h) {
	this->width = w;
	this->height = h;
}

void Map::drawSideMenu() {
	for (int i = 3 * (this->width) / 4; i < this->width; ++i) {
		GotoXY(i,0);
		cout << "_";
	}
}

void Map::drawLane(int num_lane) {
	for (int i = 0; i < num_lane - 1; ++i) {
		for (int j = 0; j < 3 * (this->width) / 4; ++j) {
			GotoXY(j+1,5);
			cout << "_";
		}
	}
}

void mapThread(Map* m) {
	int w, h;
	GetConsoleSize(w, h);
	for (int i = 0; i < (3 * w) / 4; ++i)
		cout << "_";
	for (int i = 0; i < (3 * w) / 4; ++i) {
		GotoXY(0, h);
		cout << "_";
	}
	for (int j = 0; j < h; ++j) {
		GotoXY(1, j);
		cout << "|" << endl;
	}
}

/*void Map::drawMap(int w, int h) {
	ClearBackground();
	this->isRunning = true;
	thread mapthrd(mapThread, this);

	mapthrd.join();
}

Map::~Map() {}