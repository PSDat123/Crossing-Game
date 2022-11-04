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
	int w, h, cx, optionY = 13, offsetX = 5;
	GetConsoleSize(w, h);
	cx = w / 2;
	m->printTitle(cx - m->titleSize / 2, 5);

	for (int i = 0; i < m->options.size(); i++) {
		GotoXY(cx - offsetX, optionY + i);
		switch (m->options[i]) {
		case OPTIONS::CONTINUE:
			cout << "Continue";
			break;
		case OPTIONS::NEW_GAME:
			cout << "New Game";
			break;
		case OPTIONS::LOAD_GAME:
			cout << "Load Game";
			break;
		case OPTIONS::SETTINGS:
			cout << "Settings";
			break;
		case OPTIONS::CREDIT:
			cout << "Credit";
			break;
		case OPTIONS::EXIT:
			cout << "Exit";
			break;
		}
	}
	GotoXY(cx - offsetX - 3, optionY + m->curSelected);
	cout << ">> ";

	do {
		if (m->curSelected != m->prevSelected) {
			GotoXY(cx - offsetX - 3, optionY + m->prevSelected);
			cout << "  ";
			GotoXY(cx - offsetX - 3, optionY + m->curSelected);
			cout << ">> ";
			m->prevSelected = m->curSelected;
		}



	} while (m->isRunning);
}

OPTIONS MainMenu::runMenu() {
	int key = 0;
	ClearBackground();
	isRunning = true;
	thread mThread(menuThread, this);

	do {
		key = _getch();

		if (key == UP_ARROW) {
			prevSelected = curSelected;
			curSelected--;
			if (curSelected == -1) {
				curSelected = 4;
			}
		}

		if (key == DOWN_ARROW) {
			prevSelected = curSelected;
			curSelected++;
			if (curSelected == options.size()) {
				curSelected = 0;
			}
		}

	} while (key != ENTER_KEY);
	isRunning = false;
	mThread.join();
	return OPTIONS(curSelected);
}

MainMenu::~MainMenu() {}