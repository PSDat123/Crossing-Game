#include "Map.h"

Map::Map(int w, int h) {
	this->width = w;
	this->height = h;
}

void Map::drawOutline(Console* c) {
	c->DrawHorizontalLine(L'═', 0);
	c->DrawHorizontalLine(L'═', height - 1);
	c->DrawVerticalLine(L'║', 0);
	c->DrawVerticalLine(L'║', width - height);
	c->DrawVerticalLine(L'║', width - 1);
	c->DrawChar(L'╔', 0, 0);
	c->DrawChar(L'╗', width - 1, 0);
	c->DrawChar(L'╦', width - height, 0);
	c->DrawChar(L'╚', 0, height - 1);
	c->DrawChar(L'╩', width - height, height - 1);
	c->DrawChar(L'╝', width - 1, height - 1);
}

Map::~Map() {}