#pragma once
#include "Console.h"
#include "Lane.h"

class Map {
public:
	static vector<vector<wstring>> digits;
	Map(int w, int h, int num_lane, int* level, int* score);
	~Map();
	void drawOutline(Console*);
	void drawMain(Console*);
	void updateMain();
private:
	int side_x;
	int width, height;
	int* cur_level;
	int* cur_score;
	vector<Lane> lanes;
};