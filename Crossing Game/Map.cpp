#include "Map.h"

Map::Map(int w, int h) {
	this->width = w;
	this->height = h;
}

void Map::drawMap() {
	GotoXY(0, 0);
	wcout << L"╔";
	for (int i = 2; i < width; ++i) {
		wcout << L"═";
	}
	wcout << L"╗";
	// Left
	for (int j = 1; j < height - 1; ++j) {
		GotoXY(0, j);
		wcout << L"║" << endl;
	}
	// Middle
	int off = width - height;
	GotoXY(off, 0);
	wcout << L"╦";
	for (int j = 1; j < height - 1; ++j) {
		GotoXY(off, j);
		wcout << L"║" << endl;
	}
	// Right
	for (int j = 1; j < height - 1; ++j) {
		GotoXY(width - 1, j);
		wcout << L"║" << endl;
	}

	//Bottom
	GotoXY(0, height - 1);
	wcout << L"╚";
	for (int i = 2; i < width; ++i) {
		wcout << L"═";
	}
	wcout << L"╝";

	GotoXY(off, height - 1);
	wcout << L"╩";
	
}

Map::~Map() {}