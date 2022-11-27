#include "Map.h"

Map::Map(int w, int h) {
	this->width = w;
	this->height = h;
}

void Map::drawOutline(Console* c) {
	vector<wstring> score_text = {
		L"╔═══╗╔═══╗╔═══╗╔═══╗╔═══╗",
		L"║    ║    ║   ║║   ║║",
		L"╚═══╗║    ║   ║╠══╦╝╠═══",
		L"    ║║    ║   ║║  ║ ║",
		L"╚═══╝╚═══╝╚═══╝╝  ╚═╚═══╝",
	};

	vector<wstring> lv_text = {
		L"╔    ╔═══╗╔   ╗╔═══╗╔      ",
		L"║    ║    ║   ║║    ║      □",
		L"║    ╠═══ ║   ║╠═══ ║      ",
		L"║    ║    ╚╗ ╔╝║    ║      □",
		L"╚═══╝╚═══╝ ╚═╝ ╚═══╝╚═══╝  "
	};
	vector<wstring> car = {
		L" _.-.___\\__",
		L"|)        _`-.",
		L"'-(o)----(o)--`"
	};

	vector<vector<wstring>> num = {
	{   L"╔═══╗",
		L"║ ║ ║",
		L"║ ║ ║",
		L"║ ║ ║",
		L"╚═══╝"},
	{	L"╔══╗",
		L"╚╗ ║",
		L" ║ ║",
		L" ║ ║",
		L" ╚═╝"},
	{	L"╔═══╗",
		L"╚═╗ ║",
		L"╔═══╝",
		L"║ ╚═╗",
		L"╚═══╝"},
	{	L"╔═══╗",
		L"╚═╗ ║",
		L" ═══╣",
		L"╔═╝ ║",
		L"╚═══╝"},
	};
	int off = width - height - 3, num_lane = 0, controlY = 31;
	string lv_unit = "1";
	string lv_tenth = "0"
		;
	string hundred = "1";
	string tenth = "2";
	string unit = "3";
	//Top and bottom line
	c->DrawHorizontalLine(L'═', 0, 0, 0);
	c->DrawHorizontalLine(L'═', 0, 0, height - 1);

	c->DrawVerticalLine(L'║', 0); // Left col
	c->DrawVerticalLine(L'║', off); // Mid col
	c->DrawVerticalLine(L'║', width - 1); //Right col
	for (int i = height - 6; i > 0; i -= 6) {
		if (i == height - 6 || num_lane == 4) {
			c->DrawHorizontalLine(L'═', 0, height + 3, i);
			c->DrawChar(L'╠', 0, i);
			c->DrawChar(L'╣', off, i);
		}
		else if (num_lane < 5) {
			num_lane++;
			c->DrawHorizontalLine(L'─', 0, height + 3, i);
			c->DrawChar(L'╟', 0, i);
			c->DrawChar(L'╢', off, i);
		}
	}

	//Small title (Top panel)
	c->DrawString(L"============== THE JAYWALKER =============", off + 1, 1);
	c->DrawString(L"MADE BY GROUP 1 - 21CLC05", off + 10, 2);
	c->DrawString(L"╔═══ PLAYER NAME ═══╗ ", off + 12, 3);
	c->DrawString(L"║                   ║ ", off + 12, 4);
	c->DrawString(L"╚═══════════════════╝ ", off + 12, 5);
	for (int i = 0; i < car.size(); ++i) {
		c->DrawString(car[i], off + 15, 6 + i);
	}
	for (int i = 0; i < lv_text.size(); ++i) {
		c->DrawString(lv_text[i], off + 2, 10 + i);
		c->DrawString(num[stoi(lv_tenth)][i], off + 33, 10 + i);
		c->DrawString(num[stoi(lv_unit)][i], off + 38, 10 + i);
	}

	//Score box
	c->DrawHorizontalLine(L'═', off, off + 1, 15);
	c->DrawChar(L'╠', off, 15);
	c->DrawChar(L'╣', width - 1, 15);

	//Score panel (Middle panel)
	for (int i = 0; i < score_text.size(); ++i) {
		c->DrawString(score_text[i], off + 9, 17 + i);
		c->DrawString(num[stoi(hundred)][i], off + 14, 23 + i);
		c->DrawString(num[stoi(tenth)][i], off + 19, 23 + i);
		c->DrawString(num[stoi(unit)][i], off + 24, 23 + i);
	}

	//Center box
	c->DrawHorizontalLine(L'═', off, off + 1, 30);
	c->DrawChar(L'╠', off, 30);
	c->DrawChar(L'╣', width - 1, 30);

	//Keyboard control (Bottom panel)
	c->DrawString(L"KEYBOARD CONTROL", off + 1, controlY++);
	c->DrawString(L"W to go up", off + 1, controlY++);
	c->DrawString(L"S to go down", off + 1, controlY++);
	c->DrawString(L"A to go left", off + 1, controlY++);
	c->DrawString(L"D to go right", off + 1, controlY++);
	c->DrawString(L"P to pause/unpause game", off + 1, controlY++);
	c->DrawString(L"S to save game", off + 1, controlY++);
	c->DrawString(L"L to load game", off + 1, controlY++);

	//Corner and T pieces
	c->DrawChar(L'╔', 0, 0);
	c->DrawChar(L'╗', width - 1, 0);
	c->DrawChar(L'╦', off, 0);
	c->DrawChar(L'╚', 0, height - 1);
	c->DrawChar(L'╩', off, height - 1);
	c->DrawChar(L'╝', width - 1, height - 1);
}

Map::~Map() {}