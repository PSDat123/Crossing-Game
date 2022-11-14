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
	this->options = { OPTIONS::CONTINUE, OPTIONS::NEW_GAME, OPTIONS::LOAD_GAME, OPTIONS::SETTINGS, OPTIONS::CREDIT, OPTIONS::EXIT};
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
		switch (m->options[i]) {
		case OPTIONS::CONTINUE:
			wcout << L"█      Continue     █║";
			break;
		case OPTIONS::NEW_GAME:
			wcout << L"█      New Game     █║";
			break;
		case OPTIONS::LOAD_GAME:
			wcout << L"█      Load Game    █║";
			break;
		case OPTIONS::SETTINGS:
			wcout << L"█      Settings     █║";
			break;
		case OPTIONS::CREDIT:
			wcout << L"█      Credit       █║";
			break;
		case OPTIONS::EXIT:
			wcout << L"█      Exit         █║";
			break;
		}
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
	Car car(0, roadY + 1);
	do {
		if (m->curSelected != m->prevSelected) {
			GotoXY(cx - offsetX + 3, optionY + m->prevSelected);
			wcout << L"  ";
			GotoXY(cx - offsetX + 3, optionY + m->curSelected);
			wcout << L"► ";
			m->prevSelected = m->curSelected;
		}

		car.draw();
		car.move(DIRECTION::RIGHT);
		if (!car.getState()) {
			car = Car(0, roadY + 1);
		}
		Sleep(30);
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
		Sleep(30);
	} while (key != ENTER_KEY);
	this->isRunning = false;
	mThread.join();
	return this->options[this->curSelected];
}

MainMenu::~MainMenu() {}