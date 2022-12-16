#pragma once
#include "Console.h"
#include "Lane.h"
#include "People.h"

class Map {
public:
	static vector<vector<wstring>> digits;
	static vector<wstring> score_text;
	static vector<wstring> level_text;

	Map(int w, int h, int num_lane, People* character, int* level, int* score);
	~Map();
	void drawOutline(Console*);
	void drawMain(Console*);
	void updateMain(Console*);
	void resetCharacter();
	bool checkCollision(People*);
	bool checkFinished(People*);
	bool updateScore();
	void drawScoreText(Console* c);
	void saveScore();
	void drawLevelText(Console* c);
	void drawLiveText(Console* c);
	void nextLevel(Console* c);
private:
	int side_x;
	int width, height, num_lane;
	int* cur_level;
	int temp_score;
	int* cur_score;
	People* character;
	deque<Lane> lanes;
	deque<bool> visited;
};