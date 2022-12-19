#include "Map.h"

Map::Map(int w, int h, int num_lane, People* character, int* level, int* score) {
	this->width = w;
	this->height = h;
	this->num_lane = num_lane;
	this->character = character;
	this->cur_level = level;
	this->cur_score = score;
	this->temp_score = *score;
	side_x = int(width * 0.7f);
	if (width - side_x < 43) side_x = width - 43;
	for (int i = num_lane - 1; i >= 0; --i) {
		lanes.push_back(Lane(1, 4 + i * 6, side_x - 1, 5));
		lanes.back().setDirection((i & 1 ? DIRECTION::LEFT : DIRECTION::RIGHT));
		lanes.back().setMinDist(1 + (60 / (*cur_level + 1)));
		lanes.back().setSpeed(0.3);
		for (int j = 1; j <= *level; ++j) {
			lanes.back().increaseSpeed(1.0f / (3.0f * (j + 1)));
		}
		visited.push_back(false);
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
		L" ╔══╗",
		L" ╚╗ ║",
		L"  ║ ║",
		L"  ║ ║",
		L"  ╚═╝"
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

vector<wstring> Map::score_text = {
		L"╔═══╗╔═══╗╔═══╗╔═══╗╔═══╗",
		L"║    ║    ║   ║║   ║║    ",
		L"╚═══╗║    ║   ║╠══╦╝╠═══ ",
		L"    ║║    ║   ║║  ║ ║    ",
		L"╚═══╝╚═══╝╚═══╝╝  ╚═╚═══╝",
};

vector<wstring> Map::level_text = {
		L"╔    ╔═══╗╔   ╗╔═══╗╔    ",
		L"║    ║    ║   ║║    ║    ",
		L"║    ╠═══ ║   ║╠═══ ║    ",
		L"║    ║    ╚╗ ╔╝║    ║    ",
		L"╚═══╝╚═══╝ ╚═╝ ╚═══╝╚═══╝"
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
	vector<wstring> car = Car::spriteSheet[DIRECTION::RIGHT][1];

	
	int controlY = height - 8, m;
	//Top and bottom line
	c->DrawHorizontalLine(L'═', 0, width - 1, 0);
	c->DrawHorizontalLine(L'═', 0, width - 1, height - 1);

	c->DrawVerticalLine(L'║', 0, 0, height - 1); // Left col
	c->DrawVerticalLine(L'║', side_x, 0, height - 1); // Mid col
	c->DrawVerticalLine(L'║', width - 1, 0, height - 1); //Right col

	//Small title (Top panel)
	m = width + side_x;
	c->DrawHorizontalLine(L'=', side_x + 1, width - 2, 1);
	c->DrawString(L" THE JAYWALKER ", (m - 15) / 2, 1);
	c->DrawString(L"MADE BY GROUP 1 - 21CLC05", (m - 25) / 2, 2);
	c->DrawString(L"╔═══ PLAYER NAME ═══╗", (m - 21) / 2, 3);
	c->DrawString(L"║                   ║", (m - 21) / 2, 4);
	c->DrawString(L"╚═══════════════════╝", (m - 21) / 2, 5);
	char* name = character->getName();
	wstring tmp = L"LIVE: " + to_wstring(character->getLife()) + L" ♥";
	c->DrawString(wstring(name, name + strlen(name)), (m - strlen(name)) / 2 , 4);
	c->DrawHorizontalLine(L' ', (m - tmp.size()) / 2 - 1, (m + tmp.size()) / 2, 6);
	c->DrawString(tmp, (m - tmp.size()) / 2, 6);


	vector<wstring> level = numToAsciiDigits(*cur_level);
	m = (width + side_x - level_text[0].size() + 2) / 2;
	for (size_t i = 0; i < level_text.size(); ++i) {
		c->DrawString(level_text[i], m, i + 7);
	}
	m = (width + side_x - level[0].size()) / 2;
	for (size_t i = 0; i < level.size() ;++i) {
		c->DrawString(level[i], m, i + 13);
	}
	//Score box
	c->DrawHorizontalLine(L'═', side_x + 1, width - 2, 20);
	c->DrawChar(L'╠', side_x, 20);
	c->DrawChar(L'╣', width - 1, 20);

	
	//Score panel (Middle panel)
	vector<wstring> score = numToAsciiDigits(temp_score);
	m = (width + side_x - score_text[0].size()) / 2;
	for (size_t i = 0; i < score_text.size(); ++i) {
		c->DrawString(score_text[i], m, i + 22);
	}
	m = (width + side_x - score[0].size()) / 2;
	for (size_t i = 0; i < score.size(); ++i) {
		c->DrawString(score[i], m, i + 28);
	}

	//Center box
	c->DrawHorizontalLine(L'═', side_x + 1, width - 2, height - 9);
	c->DrawChar(L'╠', side_x, height - 9);
	c->DrawChar(L'╣', width - 1, height - 9);

	//Keyboard control (Bottom panel)
	m = width + side_x;
	c->DrawString(L"KEYBOARD CONTROL", (m - 16) / 2, controlY++);
	c->DrawString(L"W to go up", (m - 10) / 2, controlY++);
	c->DrawString(L"S to go down", (m - 12) / 2, controlY++);
	c->DrawString(L"A to go left", (m - 12) / 2, controlY++);
	c->DrawString(L"D to go right", (m - 13) / 2, controlY++);
	c->DrawString(L"ESC to pause/unpause game", (m - 23) / 2, controlY++);
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

void Map::updateMain(Console* console) {
	for (Lane& lane : lanes) {
		if (lane.getY() > 0 && lane.getY() + lane.getHeight() < height - 1) {
			lane.updateVehicles(console);
			lane.updateTraffic();
		}
	}
	if (!lanes.empty() && lanes.front().getY() >= height - 1) {
		lanes.pop_front();
		visited.pop_front();
	}
}

void Map::drawMain(Console* c) {
	for (Lane& lane : lanes) {
		if (lane.getY() + lane.getHeight() < height - 2) {
			lane.drawAll(c);
		}
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

bool Map::updateScore() {
	for (int i = 0; i < visited.size(); ++i) {
		if (visited[i]) continue;
		if (lanes[i].isInLane(this->character)) {
			visited[i] = true;
			temp_score += 1;
			return true;
		}
		return false;
	}
	return false;
}

void Map::drawScoreText(Console* c) {
	vector<wstring> score = numToAsciiDigits(temp_score);
	int m = (width + side_x - score[0].size()) / 2;
	for (size_t i = 0; i < score.size(); ++i) {
		c->DrawString(score[i], m, i + 28);
	}
}

bool Map::checkFinished(People* p) {
	if (p->getY() + p->getHeight() - 1 < lanes.back().getY()) return true;
	return false;
}

void Map::saveScore() {
	*this->cur_score = this->temp_score;
}

void Map::drawLevelText(Console* c) {
	vector<wstring> level = numToAsciiDigits(*cur_level);
	int m = (width + side_x - level[0].size()) / 2;
	for (size_t i = 0; i < level.size(); ++i) {
		c->DrawString(level[i], m, i + 13);
	}
}

void Map::drawLiveText(Console* c) {
	wstring tmp = L"LIVE: " + to_wstring(character->getLife()) + L" ♥";
	int m = width + side_x;
	c->DrawHorizontalLine(L' ', (m - tmp.size()) / 2 - 1, (m + tmp.size()) / 2, 6);
	c->DrawString(tmp, (m - tmp.size()) / 2, 6);
}

void Map::nextLevel(Console* c) {
	for (int i = 0; i < num_lane; ++i) {
		lanes.push_back(Lane(1, -height + 3 + (num_lane - i) * 6, side_x - 1, 5));
		lanes.back().setDirection((i & 1 ? DIRECTION::LEFT : DIRECTION::RIGHT));
		lanes.back().setMinDist(1 + (60 / (*cur_level + 1)));
		lanes.back().increaseSpeed(1.0f / (3.0f * (*cur_level + 1)));
		visited.push_back(false);
	}
	this_thread::sleep_for(chrono::milliseconds(INTERVAL * 3));
	for (int i = 0; i < height - 2 - this->character->getHeight(); ++i) {
		c->ShiftDown({ 1, 1, SHORT(side_x - 1), SHORT(height - 2) });
		for (Lane& lane : lanes) {
			lane.move(DIRECTION::DOWN);
		}
		character->setPos(character->getX(), character->getY() + 1);
		updateMain(c);
		drawMain(c);
		c->UpdateScreen();
		this_thread::sleep_for(chrono::milliseconds(INTERVAL));
	}
}
Map::~Map() {}