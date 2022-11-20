#include "MainMenu.h"

MainMenu::MainMenu() {
	this->title = {
		L"████████╗██╗  ██╗███████╗         ██╗ █████╗ ██╗   ██╗██╗    ██╗ █████╗ ██╗     ██╗  ██╗███████╗██████╗ ",
		L"╚══██╔══╝██║  ██║██╔════╝         ██║██╔══██╗╚██╗ ██╔╝██║    ██║██╔══██╗██║     ██║ ██╔╝██╔════╝██╔══██╗",
		L"   ██║   ███████║█████╗           ██║███████║ ╚████╔╝ ██║ █╗ ██║███████║██║     █████╔╝ █████╗  ██████╔╝",
		L"   ██║   ██╔══██║██╔══╝      ██   ██║██╔══██║  ╚██╔╝  ██║███╗██║██╔══██║██║     ██╔═██╗ ██╔══╝  ██╔══██╗",
		L"   ██║   ██║  ██║███████╗    ╚█████╔╝██║  ██║   ██║   ╚███╔███╔╝██║  ██║███████╗██║  ██╗███████╗██║  ██║",
		L"   ╚═╝   ╚═╝  ╚═╝╚══════╝     ╚════╝ ╚═╝  ╚═╝   ╚═╝    ╚══╝╚══╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝"
	};
	this->options = { 
		{OPTIONS::CONTINUE, L"Continue"},
		{OPTIONS::NEW_GAME, L"New Game"},
		{OPTIONS::LOAD_GAME, L"Load Game"},
		{OPTIONS::SETTINGS, L"Settings"},
		{OPTIONS::CREDIT, L"Credit"},
		{OPTIONS::EXIT, L"Exit"}
	};
	this->curSelected = 0;
}

void MainMenu::printTitle(int x, int y) {
	for (int i = 0; i < this->title.size(); ++i) {
		GotoXY(x, y + i);
		wcout << this->title[i];
	}
	wcout << endl;
}

void menuThread(MainMenu* m) {
	int w, h, cx, optionY = 16, offsetX = 11, roadY;
	GetConsoleSize(w, h);
	roadY = h - 10;
	cx = w / 2;
	m->printTitle(cx - m->title[0].size() / 2, 5);

	GotoXY(cx - offsetX, optionY - 2);
	wcout << L"█████████████████████╗";
	GotoXY(cx - offsetX, optionY - 1);
	wcout << L"█                   █║";
	for (int i = 0; i < m->options.size(); i++) {
		GotoXY(cx - offsetX, optionY + i);
		wcout << L"█                   █║";
		GotoXY(cx - offsetX + 7, optionY + i);
		wcout << m->options[i].second;
	}
	GotoXY(cx - offsetX, optionY + m->options.size());
	wcout << L"█                   █║";
	GotoXY(cx - offsetX, optionY + m->options.size() + 1);
	wcout << L"█████████████████████║";
	GotoXY(cx - offsetX, optionY + m->options.size() + 2);
	wcout << L"╚════════════════════╝";
	GotoXY(cx - offsetX + 3, optionY + m->curSelected);
	wcout << L"► ";


	GotoXY(0, roadY);
	for (int i = 0; i < w; ++i) {
		wcout << L"—";
	}
	GotoXY(0, roadY + 6);
	for (int i = 0; i < w; ++i) {
		wcout << L"—";
	}
	srand(time(NULL));
	deque<Car> qCar;
	int count = 0;
	qCar.push_back(Car(-1, roadY + 1, w, h));
	do {
		if (m->curSelected != m->prevSelected) {
			GotoXY(cx - offsetX + 3, optionY + m->prevSelected);
			wcout << L"  ";
			GotoXY(cx - offsetX + 3, optionY + m->curSelected);
			wcout << L"► ";
			bool sound = PlaySound(_T("Sound/button.wav"), NULL, SND_ASYNC);
			m->prevSelected = m->curSelected;
		}
		if (!qCar.empty()) {
			for (Car& car : qCar) {
				car.draw();
				car.move(DIRECTION::RIGHT);
			}
			++count;
			if (count > qCar.back().getLength() + 7) {
				if (!(rand() % 30)) {
					qCar.push_back(Car(-1, roadY + 1, w, h));
					count = 0;
				}
			}
			if (!qCar.front().getState()) {
				qCar.pop_front();
			}
		}
		else {
			qCar.push_back(Car(-1, roadY + 1, w, h));
			count = 0;
		}
		
		Sleep(INTERVAL);
	} while (m->isRunning);
}

OPTIONS MainMenu::runMenu() {
	int key = 0;
	ClearBackground();
	isRunning = true;
	thread mThread(menuThread, this);

	do {
		key = toupper(_getch());

		if (key == UP_ARROW) {
			prevSelected = curSelected;
			curSelected--;
			if (curSelected == -1) {
				curSelected = options.size() - 1;
			}
		}

		if (key == DOWN_ARROW) {
			prevSelected = curSelected;
			curSelected++;
			if (curSelected == options.size()) {
				curSelected = 0;
			}
		}
		Sleep(INTERVAL);
	} while (key != ENTER_KEY);
	this->isRunning = false;
	mThread.join();
	return this->options[this->curSelected].first;
}

MainMenu::~MainMenu() {}