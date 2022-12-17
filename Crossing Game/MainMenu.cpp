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
	this->console->GetConsoleSize(width, height);
}

void MainMenu::printTitle(int x, int y) {
	for (size_t i = 0; i < this->title.size(); ++i) {
		console->DrawString(title[i], x, y + (int)i);
	}
}

void menuThread(MainMenu* m) {
	srand(static_cast<unsigned int>(time(NULL)));
	SHORT cx, optionY = 16, offsetX = 11, roadY, decorY;
	roadY = m->height - 10;
	decorY = roadY - 13;
	cx = m->width / 2;

	//Background decor
	m->console->DrawString(L"┌——————————————┐                                   .————.                       .———————.",                                                      0, decorY++);
	m->console->DrawString(L"│[]  []  []  []│         .————————————————.    .———'    '———.                 .' .—————. '.                 ┌——————————————————————————————┐",   0, decorY++);
	m->console->DrawString(L"│[]  []  []  []│         │  GRAND  HOTEL  │    │|| ||  || ||│               .'  │       │  '.               │            HOSPITAL          │",   0, decorY++);
    m->console->DrawString(L"│[]  []  []  []│     .-——┴————————————————┴——-.│|| ||  || ||│               │   │       │   │               │   [_] [_] [_]  [_] [_] [_]   │",   0, decorY++);
	m->console->DrawString(L"│[]  []  []  []│     │ [_]  [_]  []  [_]  [_] ││|| ||  || ||│               │    '—————'    │               │   [_] [_] [_]  [_] [_] [_]   │",   0, decorY++);
	m->console->DrawString(L"│[]  []  []  []│     │ [_]  [_]  []  [_]  [_] ││|| ||  || ||│               │  HIGH  SCHOOL │               │   [_] [_] [_]  [_] [_] [_]   │",   0, decorY++);
	m->console->DrawString(L"│[]  []  []  []│     │ [_]  [_]  []  [_]  [_] ││|| ||  || ||│  /\\  ┌————————┤  || || || ||  ├————————┐  /\\  │   [_] [_] [_]  [_] [_] [_]   │", 0, decorY++);
	m->console->DrawString(L"│[]  []  []  []│     │ [_]  [_]  []  [_]  [_] ││|| ||  || ||│ /  \\ │ []  [] │  || || || ||  │ []  [] │ /  \\ │   [_] [_] [_]  [_] [_] [_]   │", 0, decorY++);
	m->console->DrawString(L"│[]  []  []  []│     │ [_]  [_]  []  [_]  [_] ││|| ||  || ||│ /  \\ │ []  [] │  || || || ||  │ []  [] │ /  \\ │   [_] [_] [_]  [_] [_] [_]   │", 0, decorY++);
	m->console->DrawString(L"│[]  []  []  []├———— │ [_]  [_]  []  [_]  [_] ││|| ||  || ||│ /  \\ │ []  [] │  || || || ||  │ []  [] │ /  \\ │   [_] [_] [_]  [_] [_] [_]   │", 0, decorY++);
	m->console->DrawString(L"│[]  ┌————┐  []│||||\\│          ┌——┐          ││|| ||  || ||│ '┐┌' │ []  [] │     ┌———┐     │ []  [] │ '┐┌' │   [_] [_]  ┌————┐  [_] [_]   │",  0, decorY++);
	m->console->DrawString(L"│    │ .. │    │    ││          │  │          ││|| ||  || ||│  ││  │ []  [] │     │   │     │ []  [] │  ││  │            │    │            │",   0, decorY++);
	m->console->DrawString(L"└————┴————┴————┴————┴┴——————————┴——┴——————————┴┴————————————┴——┴┴——┴————————┴—————┴———┴—————┴————————┴——┴┴——┴————————————┴————┴————————————┘",   0, decorY);

	//Menu box
	m->printTitle(cx - (int)(m->title[0].size()) / 2, 5);
	m->console->DrawString(L"█████████████████████╗", cx - offsetX, optionY - 2);
	m->console->DrawString(L"█                   █║", cx - offsetX, optionY - 1);
	for (size_t i = 0; i < m->options.size(); i++) {
		m->console->DrawString(L"█                   █║", cx - offsetX, optionY + (int)i);
		m->console->DrawString(m->options[i].second, cx - offsetX + 7, optionY + (int)i);
	}
	m->console->DrawString(L"█                   █║", cx - offsetX, optionY + (int)m->options.size());
	m->console->DrawString(L"█████████████████████║", cx - offsetX, optionY + (int)m->options.size() + 1);
	m->console->DrawString(L"╚════════════════════╝", cx - offsetX, optionY + (int)m->options.size() + 2);
	m->console->DrawString(L"► ", cx - offsetX + 3, optionY + m->curSelected);

	//Road
	Lane lane(0, roadY, m->width, 5);
	lane.drawLane(m->console);

	do {
		if (m->curSelected != m->prevSelected) {
			m->console->DrawString(L"  ", cx - offsetX + 3, optionY + m->prevSelected);
			m->console->DrawString(L"► ", cx - offsetX + 3, optionY + m->curSelected);
			m->prevSelected = m->curSelected;
		}
		lane.updateVehicles(m->console);
		lane.drawVehicles(m->console);
		m->console->UpdateScreen();
		this_thread::sleep_for(chrono::milliseconds(INTERVAL));
	} while (m->isRunning);
}

OPTIONS MainMenu::runMenu() {
	int key = 0;
	console->ClearBackground();
	isRunning = true;
	thread mThread(menuThread, this);
	do {
		key = toupper(_getch());
		if (key == 224) key = toupper(_getch());
		if (key == UP_ARROW || key == W) {
			prevSelected = curSelected;
			curSelected--;
			if (curSelected == -1) {
				curSelected = (int)options.size() - 1;
			}
		}
		if (key == DOWN_ARROW || key == S) {
			prevSelected = curSelected;
			curSelected++;
			if (curSelected == options.size()) {
				curSelected = 0;
			}
		}
		this_thread::sleep_for(chrono::milliseconds(INTERVAL));
	} while (key != ENTER_KEY);
	this->isRunning = false;
	mThread.join();
	return this->options[this->curSelected].first;
}

MainMenu::~MainMenu() {}