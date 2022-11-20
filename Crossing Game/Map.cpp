#include "Map.h"

Map::Map(int w, int h) {
	this->width = w;
	this->height = h;
	this->isRunning = true;
}

void Map::drawSideMenu() {
	for (int i = 3 * (this->width) / 4; i < this->width; ++i) {
		GotoXY(i,0);
		wcout << L"_";
	}
}

void Map::drawLane(int num_lane) {
	wstring lane = L"";
	lane.append(3 * (this->width) / 4, L'_');
	for (int i = 0; i < num_lane + 1; ++i) {
		GotoXY(0, i * 5);
		wcout << lane;
	}
}

void mapThread(Map* m) {
	int w, h;
	GetConsoleSize(w, h);
	for (int i = 0; i < (3 * w) / 4; ++i)
		wcout << L"_";
	for (int i = 0; i < (3 * w) / 4; ++i) {
		GotoXY(0, h);
		wcout << L"_";
	}
	for (int j = 0; j < h; ++j) {
		GotoXY(1, j);
		wcout << L"|" << endl;
	}
}

void Map::drawMap() {
	drawLane(5);

	//for (int i = 0; i < (3 * width) / 4; ++i)
	//	wcout << L"_";
	/*for (int i = 0; i < (3 * width) / 4; ++i) {
		GotoXY(0, height - 2);
		wcout << L"_";
	}*/
	//for (int j = 0; j < height; ++j) {
	//	GotoXY(1, j);
	//	wcout << L"|" << endl;
	//}
}

Map::~Map() {}
