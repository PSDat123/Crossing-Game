#include "Game.h"

Game::Game(Console* screen) {
	isPaused = false;
	isRunning = true;
	console = screen;
	console->GetConsoleSize(width, height);
}

void gameThread(Game* g) {
	Map map(g->width, g->height);
	map.drawOutline(g->console);
	do{
		g->console->UpdateScreen();
		Sleep(INTERVAL);
	} while (g->isRunning);
}

void Game::exitGame(thread* t) {
	console->ClearBackground();
	console->UpdateScreen();
	isRunning = false;
	t->join();
}

void Game::printCredit(int x, int y) {
	console->DrawString(L"███████████████████████████████╗", x, y++);
	console->DrawString(L"█                             █║", x, y++);
	console->DrawString(L"█       Made by Group 1       █║", x, y++);
	console->DrawString(L"█                             █║", x, y++);
	console->DrawString(L"█  Phùng Siêu Đạt - 21127243  █║", x, y++);
	console->DrawString(L"█  Quách Tấn Dũng - 21127247  █║", x, y++);
	console->DrawString(L"█  Đặng Hà Huy    - 21127296  █║", x, y++);
	console->DrawString(L"█  Nguyễn Cát Huy - 21127300  █║", x, y++);
	console->DrawString(L"█                             █║", x, y++);
	console->DrawString(L"███████████████████████████████║", x, y++);
	console->DrawString(L"╚══════════════════════════════╝", x, y++);
	console->DrawString(L"Press Enter to return to menu", x, y);
	console->UpdateScreen();
}

void Game::startGame() {
	MainMenu m(console);

menu:
	OPTIONS opt = m.runMenu();
	
	switch (opt) {
	case OPTIONS::CONTINUE:
		break;
	case OPTIONS::NEW_GAME:
		break;
	case OPTIONS::LOAD_GAME:
		break;
	case OPTIONS::SETTINGS:
		break;
	case OPTIONS::CREDIT:{
		console->ClearBackground();
		printCredit((width / 2) - 16, (height / 2) - 5);

		int key;
		do {
			key = toupper(_getch());
		} while (key != ENTER_KEY);
		goto menu;
		break;
	}
	case OPTIONS::EXIT:
		console->ClearBackground();
		console->UpdateScreen();
		return;
		break;
	}

	console->ClearBackground();
	thread t1(gameThread, this);
	while (true) {
		int keyInput = toupper(_getch());
		if (keyInput == 27) {
			exitGame(&t1);
			return;
		}
	}
}

Game::~Game() {}