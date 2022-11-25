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
	for (size_t i = 0; i < this->title.size(); ++i) {
		console->DrawString(title[i], x, y + i);
	}
}

Vehicle getRandomVehicle(int x, int y, int max_x, int max_y) {
	int r = rand() % 10;
	if (r == 0) {
		return Truck(x, y, max_x, max_y);
	}
	return Car(x, y, max_x, max_y);
}

void menuThread(MainMenu* m) {
	SHORT w, h, cx, optionY = 16, offsetX = 11, roadY;
	m->console->GetConsoleSize(w, h);
	roadY = h - 10;
	cx = w / 2;
	m->printTitle(cx - m->title[0].size() / 2, 5);
	m->console->DrawString(L"█████████████████████╗", cx - offsetX, optionY - 2);
	m->console->DrawString(L"█                   █║", cx - offsetX, optionY - 1);
	for (size_t i = 0; i < m->options.size(); i++) {
		m->console->DrawString(L"█                   █║", cx - offsetX, optionY + i);
		m->console->DrawString(m->options[i].second, cx - offsetX + 7, optionY + i);
	}
	m->console->DrawString(L"█                   █║", cx - offsetX, optionY + m->options.size());
	m->console->DrawString(L"█████████████████████║", cx - offsetX, optionY + m->options.size() + 1);
	m->console->DrawString(L"╚════════════════════╝", cx - offsetX, optionY + m->options.size() + 2);
	m->console->DrawString(L"► ", cx - offsetX + 3, optionY + m->curSelected);

	m->console->DrawHorizontalLine(L'—', roadY);
	m->console->DrawHorizontalLine(L'—', roadY + 6);

	srand((int)time(NULL));
	deque<Vehicle> qVehicle;
	int count = 0;
	qVehicle.push_back(getRandomVehicle(-1, roadY + 1, w, h));
	m->console->UpdateScreen();

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
		if (!qVehicle.empty()) {
			for (Vehicle& car : qVehicle) {
				car.draw(m->console);
				car.move(DIRECTION::RIGHT);
			}
			++count;
			if (count > qVehicle.back().getLength() + 7) {
				if (!(rand() % 30)) {
					qVehicle.push_back(getRandomVehicle(-1, roadY + 1, w, h));
					count = 0;
				}
			}
			if (!qVehicle.front().getState()) {
				qVehicle.pop_front();
			}
		}
		else {
			qVehicle.push_back(getRandomVehicle(-1, roadY + 1, w, h));
			count = 0;
		}
		m->console->UpdateScreen();

		t2 = std::chrono::system_clock::now();
		chrono::duration<float> delta = t2 - t1;
		float deltaTime = delta.count() * 1000.0f;

		this_thread::sleep_for(chrono::milliseconds(INTERVAL - (int)deltaTime));
	} while (m->isRunning);
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
				curSelected = options.size() - 1;
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