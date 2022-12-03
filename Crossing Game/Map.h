#pragma once
#include "Console.h"
#include "Lane.h"
#include "People.h"

class Map {
public:
	static vector<vector<wstring>> digits;
	Map(int w, int h, int num_lane, People* character, int* level, int* score);
	~Map();
	void drawOutline(Console*);
	void drawMain(Console*);
	void updateMain();
	void resetCharacter();
	bool checkCollision(People*);
private:
	int side_x;
	int width, height;
	int* cur_level;
	int* cur_score;
	People* character;
	vector<Lane> lanes;
};