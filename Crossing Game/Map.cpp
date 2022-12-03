#include "Map.h"

Map::Map(int w, int h, int num_lane, People* character, int* level, int* score) {
	this->width = w;
	this->height = h;
	this->character = character;
	this->cur_level = level;
	this->cur_score = score;
	side_x = int(width * 0.7f);
	if (width - side_x < 43) side_x = width - 43;
	for (int i = 0; i < num_lane; ++i) {
		lanes.push_back(Lane(1, 4 + i * 6, side_x - 1, 5));
		lanes[i].setDirection((i & 1 ? DIRECTION::LEFT : DIRECTION::RIGHT));
		lanes[i].setMinDist(10);
		lanes[i].setSpeed(0.3);
	}
}
vector<vector<wstring>> Map::digits = {
	{   
		L"╔═══╗",
		L"║ ║ ║",
		L"║ ║ ║",
		L"║ ║ ║",
		L"╚═══╝"
	},
	{	
		L"╔══╗",
		L"╚╗ ║",
		L" ║ ║",
		L" ║ ║",
		L" ╚═╝"
	},
	{	
		L"╔═══╗",
		L"╚═╗ ║",
		L"╔═══╝",
		L"║ ╚═╗",
		L"╚═══╝"
	},
	{	
		L"╔═══╗",
		L"╚═╗ ║",
		L" ═══╣",
		L"╔═╝ ║",
		L"╚═══╝"
	},
	{	L"╔═╦═╗",
		L"║ ║ ║",
		L"╚═╗ ║",
		L"  ║ ║",
		L"  ╚═╝"
	},
	{	L"╔═══╗",
		L"║ ╔═╝",
		L"╚═══╗",
		L"╔═╝ ║",
		L"╚═══╝"
	},
	{	L"╔═══╗",
		L"║ ╔═╝",
		L"║ ╠═╗",
		L"║ ╚ ║",
		L"╚═══╝"
	},
	{	L"╔═══╗",
		L"╚═╗ ║",
		L" ═╬═╣",
		L"  ║ ║",
		L"  ╚═╝"
	},
	{   L"╔═══╗",
		L"║ ╦ ║",
		L"╠═╬═╣",
		L"║ ╩ ║",
		L"╚═══╝"
	},
	{   L"╔═══╗",
		L"║ ╦ ║",
		L"╚═╗ ║",
		L"╔═╝ ║",
		L"╚═══╝"
	}
};

vector<wstring> numToAsciiDigits(int n) {
	vector<wstring> res(5);
	string s = to_string(n);
	for (char& c : s) {
		for (int i = 0; i < 5; ++i) {
			res[i] += Map::digits[c - '0'][i] + L' ';
		}
	}
	for (int i = 0; i < 5; ++i) {
		res[i].pop_back();
	}
	return res;
}

void Map::drawOutline(Console* c) {
	vector<wstring> score_text = {
		L"╔═══╗╔═══╗╔═══╗╔═══╗╔═══╗",
		L"║    ║    ║   ║║   ║║    ",
		L"╚═══╗║    ║   ║╠══╦╝╠═══ ",
		L"    ║║    ║   ║║  ║ ║    ",
		L"╚═══╝╚═══╝╚═══╝╝  ╚═╚═══╝",
	};

	vector<wstring> lv_text = {
		L"╔    ╔═══╗╔   ╗╔═══╗╔       ",
		L"║    ║    ║   ║║    ║      □",
		L"║    ╠═══ ║   ║╠═══ ║       ",
		L"║    ║    ╚╗ ╔╝║    ║      □",
		L"╚═══╝╚═══╝ ╚═╝ ╚═══╝╚═══╝   "
	};
	vector<wstring> car = Car::spriteSheet[DIRECTION::RIGHT][1];

	
	int controlY = 31, m;
	//Top and bottom line
	c->DrawHorizontalLine(L'═', 0, width - 1, 0);
	c->DrawHorizontalLine(L'═', 0, width - 1, height - 1);

	c->DrawVerticalLine(L'║', 0); // Left col
	c->DrawVerticalLine(L'║', side_x); // Mid col
	c->DrawVerticalLine(L'║', width - 1); //Right col

	//Small title (Top panel)
	m = width + side_x;
	c->DrawHorizontalLine(L'=', side_x + 1, width - 2, 1);
	c->DrawString(L" THE JAYWALKER ", (m - 15) / 2, 1);
	c->DrawString(L"MADE BY GROUP 1 - 21CLC05", (m - 25) / 2, 2);
	c->DrawString(L"╔═══ PLAYER NAME ═══╗", (m - 21) / 2, 3);
	c->DrawString(L"║                   ║", (m - 21) / 2, 4);
	c->DrawString(L"╚═══════════════════╝", (m - 21) / 2, 5);
	for (int i = 0; i < car.size(); ++i) {
		c->DrawString(car[i], (m - car[0].size()) / 2, i + 6);
	}

	vector<wstring> level = numToAsciiDigits(*cur_level);
	m = (width + side_x - lv_text[0].size() - level[0].size() - 1) / 2;
	for (size_t i = 0; i < lv_text.size(); ++i) {
		c->DrawString(lv_text[i], m, i + 10);
	}
	for (size_t i = 0; i < level.size() ;++i) {
		c->DrawString(level[i], m + lv_text[0].size() + 1, i + 10);
	}
	//Score box
	c->DrawHorizontalLine(L'═', side_x + 1, width - 2, 15);
	c->DrawChar(L'╠', side_x, 15);
	c->DrawChar(L'╣', width - 1, 15);

	
	//Score panel (Middle panel)
	vector<wstring> score = numToAsciiDigits(*cur_score);
	m = (width + side_x - score_text[0].size()) / 2;
	for (size_t i = 0; i < score_text.size(); ++i) {
		c->DrawString(score_text[i], m, i + 17);
	}
	m = (width + side_x - score[0].size()) / 2;
	for (size_t i = 0; i < score.size(); ++i) {
		c->DrawString(score[i], m, i + 23);
	}

	//Center box
	c->DrawHorizontalLine(L'═', side_x + 1, width - 2, 30);
	c->DrawChar(L'╠', side_x, 30);
	c->DrawChar(L'╣', width - 1, 30);

	//Keyboard control (Bottom panel)
	m = width + side_x;
	c->DrawString(L"KEYBOARD CONTROL", (m - 16) / 2, controlY++);
	c->DrawString(L"W to go up", (m - 10) / 2, controlY++);
	c->DrawString(L"S to go down", (m - 12) / 2, controlY++);
	c->DrawString(L"A to go left", (m - 12) / 2, controlY++);
	c->DrawString(L"D to go right", (m - 13) / 2, controlY++);
	c->DrawString(L"P to pause/unpause game", (m - 23) / 2, controlY++);
	c->DrawString(L"S to save game", (m - 14) / 2, controlY++);
	c->DrawString(L"L to load game", (m - 14) / 2, controlY++);
	//Corner and T pieces
	c->DrawChar(L'╔', 0, 0);
	c->DrawChar(L'╗', width - 1, 0);
	c->DrawChar(L'╦', side_x, 0);
	c->DrawChar(L'╚', 0, height - 1);
	c->DrawChar(L'╩', side_x, height - 1);
	c->DrawChar(L'╝', width - 1, height - 1);

	for (Lane& lane : lanes) {
		lane.drawLane(c);
	}
}

void Map::updateMain() {
	for (Lane& lane : lanes) {
		lane.updateVehicles();
	}
}


void Map::drawMain(Console* c) {
	for (Lane& lane : lanes) {
		lane.drawLane(c);
		lane.drawVehicles(c);
	}
}

void Map::resetCharacter() {
	character->setPos((side_x - character->getWidth()) / 2, height - character->getHeight() - 3);
	character->setBound({ 1, 1, SHORT(side_x), SHORT(height - 1)});
}

bool Map::checkCollision(People* p) {
	for (Lane& lane : lanes) {
		if (lane.isInLane(p) && lane.checkCollison(p)) return true;
	}
	return false;
}

Map::~Map() {}