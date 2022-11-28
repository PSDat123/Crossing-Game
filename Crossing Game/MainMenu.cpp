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
	SHORT cx, optionY = 16, offsetX = 11, roadY;
	roadY = m->height - 10;
	cx = m->width / 2;
	m->printTitle(cx - m->title[0].size() / 2, 5);
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

	Lane lane(0, roadY, m->width, 5, DIRECTION::RIGHT);
	lane.drawLane(m->console);

	auto t1 = chrono::system_clock::now();
	auto t2 = t1;
	
	do {
		t1 = chrono::system_clock::now();

		if (m->curSelected != m->prevSelected) {
			PlaySound(_T("Sound/button.wav"), NULL, SND_ASYNC);
			m->console->DrawString(L"  ", cx - offsetX + 3, optionY + m->prevSelected);
			m->console->DrawString(L"► ", cx - offsetX + 3, optionY + m->curSelected);
			m->prevSelected = m->curSelected;
		}
		
		lane.updateVehicles();
		lane.drawVehicles(m->console);
		m->console->UpdateScreen();

		t2 = std::chrono::system_clock::now();
		chrono::duration<float> delta = t2 - t1;
		float deltaTime = delta.count() * 1000.0f;

		this_thread::sleep_for(chrono::milliseconds(INTERVAL - (int)deltaTime));
	} while (m->isRunning);
}

void animateExit(MainMenu* m) {
	//short offset = 5;
	//short h = m->title.size();
	//for (short i = 0; i < offset + h; ++i) {
	//	m->console->ShiftUp({ 0, (short)(offset - i), (short)(m->width - 1),  (short)(offset + h - 1 - i) });
	//	m->console->UpdateScreen();
	//	Sleep(INTERVAL);

	//}
}

OPTIONS MainMenu::runMenu() {
	int key = 0;
	console->ClearBackground();
	isRunning = true;
	thread mThread(menuThread, this);
	do {
		key = toupper(_getch());
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
	animateExit(this);
	return this->options[this->curSelected].first;
}

MainMenu::~MainMenu() {}