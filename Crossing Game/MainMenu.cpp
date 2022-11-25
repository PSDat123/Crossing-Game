#include "MainMenu.h"

MainMenu::MainMenu(Console* screen) {
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
	this->console = screen;
}

void MainMenu::printTitle(int x, int y) {
	for (int i = 0; i < this->title.size(); ++i) {
		console->DrawString(title[i], x, y + i);
	}
}
void menuThread(MainMenu* m) {
	SHORT w, h, cx, optionY = 16, offsetX = 11, roadY;
	m->console->GetConsoleSize(w, h);
	roadY = h - 10;
	cx = w / 2;
	m->printTitle(cx - m->title[0].size() / 2, 5);
	m->console->DrawString(L"█████████████████████╗", cx - offsetX, optionY - 2);
	m->console->DrawString(L"█                   █║", cx - offsetX, optionY - 1);
	for (int i = 0; i < m->options.size(); i++) {
		m->console->DrawString(L"█                   █║", cx - offsetX, optionY + i);
		m->console->DrawString(m->options[i].second, cx - offsetX + 7, optionY + i);
	}
	m->console->DrawString(L"█                   █║", cx - offsetX, optionY + m->options.size());
	m->console->DrawString(L"█████████████████████║", cx - offsetX, optionY + m->options.size() + 1);
	m->console->DrawString(L"╚════════════════════╝", cx - offsetX, optionY + m->options.size() + 2);
	m->console->DrawString(L"► ", cx - offsetX + 3, optionY + m->curSelected);

	m->console->DrawHorizontalLine(L'—', roadY);
	m->console->DrawHorizontalLine(L'—', roadY + 6);

	//wcout << L"► ";
	srand(time(NULL));
	deque<Car> qCar;
	int count = 0;
	qCar.push_back(Car(-1, roadY + 1, w, h));
	m->console->UpdateScreen();
	do {
		if (m->curSelected != m->prevSelected) {
			//PlaySound(_T("Sound/button.wav"), NULL, SND_ASYNC);
			m->console->DrawString(L"  ", cx - offsetX + 3, optionY + m->prevSelected);
			m->console->DrawString(L"► ", cx - offsetX + 3, optionY + m->curSelected);
			m->prevSelected = m->curSelected;
		}
		if (!qCar.empty()) {
			for (Car& car : qCar) {
				car.draw(m->console);
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
		m->console->UpdateScreen();
		Sleep(INTERVAL);
	} while (m->isRunning);
}

OPTIONS MainMenu::runMenu() {
	int key = 0;
	console->ClearBackground();
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