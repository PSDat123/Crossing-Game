#include "Map.h"

Map::Map(int w, int h) {
	this->width = w;
	this->height = h;
	this->isRunning = true;
}

void Map::drawMap() {
	GotoXY(0, 0);
	wcout << L"╔";
	for (int i = 0; i < width - 2; ++i) {
		if (i == (3 * width) / 4) {
			wcout << L"╦";
			for (int j = 0; j < height - 2; ++j) {
				GotoXY(i + 1, j + 1);
				wcout << L"║" << endl;
			}
		}
		else {
			GotoXY(i + 1, 0);
			wcout << L"═";
		}
	}

	GotoXY(width - 1, 0);
	wcout << L"╗";
	for (int j = 0; j < height - 2; ++j) {
		GotoXY(0, j + 1);
		wcout << L"║" << endl;
		GotoXY(width - 1, j + 1);
		wcout << L"║" << endl;
	}

	GotoXY(1, height);
	wcout << L"╚";
	for (int i = 0; i < width - 2; ++i) {
		if (i == (3 * width) / 4) {
			wcout << L"╩";
		}
		else {
			GotoXY(i + 1, height);
			wcout << L"═";
		}
	}
	GotoXY(width - 1, height);
	wcout << L"╝";
}

Map::~Map() {}
