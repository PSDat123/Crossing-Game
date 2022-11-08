#include "MainMenu.h"

MainMenu::MainMenu() {
	this->title = {
		"████████╗██╗  ██╗███████╗         ██╗ █████╗ ██╗   ██╗██╗    ██╗ █████╗ ██╗     ██╗  ██╗███████╗██████╗ ",
		"╚══██╔══╝██║  ██║██╔════╝         ██║██╔══██╗╚██╗ ██╔╝██║    ██║██╔══██╗██║     ██║ ██╔╝██╔════╝██╔══██╗",
		"   ██║   ███████║█████╗           ██║███████║ ╚████╔╝ ██║ █╗ ██║███████║██║     █████╔╝ █████╗  ██████╔╝",
		"   ██║   ██╔══██║██╔══╝      ██   ██║██╔══██║  ╚██╔╝  ██║███╗██║██╔══██║██║     ██╔═██╗ ██╔══╝  ██╔══██╗",
		"   ██║   ██║  ██║███████╗    ╚█████╔╝██║  ██║   ██║   ╚███╔███╔╝██║  ██║███████╗██║  ██╗███████╗██║  ██║",
		"   ╚═╝   ╚═╝  ╚═╝╚══════╝     ╚════╝ ╚═╝  ╚═╝   ╚═╝    ╚══╝╚══╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝"
	};
	this->titleSize = 105;
	this->options = { OPTIONS::CONTINUE, OPTIONS::NEW_GAME, OPTIONS::LOAD_GAME, OPTIONS::SETTINGS, OPTIONS::CREDIT, OPTIONS::EXIT};
	this->curSelected = 0;
}

void MainMenu::printTitle(int x, int y) {
	for (int i = 0; i < this->title.size(); ++i) {
		GotoXY(x, y + i);
		cout << this->title[i];
	}
	cout << endl;
}

void menuThread(MainMenu* m) {
	int w, h, cx, optionY = 16, offsetX = 11, roadY;
	GetConsoleSize(w, h);
	roadY = h - 10;
	cx = w / 2;
	m->printTitle(cx - m->titleSize / 2, 5);

	GotoXY(cx - offsetX, optionY - 2);
	cout << "█████████████████████╗";
	GotoXY(cx - offsetX, optionY - 1);
	cout << "█                   █║";
	for (int i = 0; i < m->options.size(); i++) {
		GotoXY(cx - offsetX, optionY + i);
		switch (m->options[i]) {
		case OPTIONS::CONTINUE:
			cout << "█      Continue     █║";
			break;
		case OPTIONS::NEW_GAME:
			cout << "█      New Game     █║";
			break;
		case OPTIONS::LOAD_GAME:
			cout << "█      Load Game    █║";
			break;
		case OPTIONS::SETTINGS:
			cout << "█      Settings     █║";
			break;
		case OPTIONS::CREDIT:
			cout << "█      Credit       █║";
			break;
		case OPTIONS::EXIT:
			cout << "█      Exit         █║";
			break;
		}
	}
	GotoXY(cx - offsetX, optionY + m->options.size());
	cout << "█                   █║";
	GotoXY(cx - offsetX, optionY + m->options.size() + 1);
	cout << "█████████████████████║";
	GotoXY(cx - offsetX, optionY + m->options.size() + 2);
	cout << "╚════════════════════╝";
	GotoXY(cx - offsetX + 3, optionY + m->curSelected);
	cout << "► ";


	GotoXY(0, roadY);
	for (int i = 0; i < w; ++i) {
		cout << "═";
	}
	GotoXY(0, roadY + 6);
	for (int i = 0; i < w; ++i) {
		cout << "═";
	}

	Vehicle car(0, roadY + 1);
	do {
		if (m->curSelected != m->prevSelected) {
			GotoXY(cx - offsetX + 3, optionY + m->prevSelected);
			cout << "  ";
			GotoXY(cx - offsetX + 3, optionY + m->curSelected);
			cout << "► ";
			m->prevSelected = m->curSelected;
		}

		car.draw();
		car.move(DIRECTION::RIGHT);
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
	isRunning = false;
	mThread.join();
	return this->options[this->curSelected];
}

MainMenu::~MainMenu() {}