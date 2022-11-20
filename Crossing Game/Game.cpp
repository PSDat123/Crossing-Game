#include "Game.h"

Game::Game() {
	this->bufferWidth = 140;
	this->bufferHeight = 50;
	this->isPaused = false;
	this->isRunning = true;
}

void gameThread(Game* g) {
	Map map(g->bufferWidth, g->bufferHeight);
	map.drawMap();
	do{
		
		Sleep(INTERVAL);
	} while (g->isRunning);
}

//void soundThread(Game* game, bool* isRunning, bool* isPause) {}

void Game::setUp() {
	MoveConsole(100, 0);
	ChangeConsoleFontSize(18);
	SetConsoleSize(this->bufferWidth, this->bufferHeight);
	SetConsoleOutputCP(CP_UTF8);
	ChangeBackground();
	FixConsoleWindow();
	ShowConsoleCursor(false);
	ClearBackground();
}

//void Game::loadGame() {}

//void Game::pauseGame() {}

void Game::exitGame(thread* t) {
	ClearBackground();
	this->isRunning = false;
	t->join();
}

void printCredit(int x=0, int y=0) {
	x -= 12;
	y -= 7;
	GotoXY(x, y);
	wcout << L"Made by Group 1: " << endl;
	GotoXY(x, y + 1);
	wcout << L"Phùng Siêu Đạt - 21127243" << endl;
	GotoXY(x, y + 2);
	wcout << L"Đặng Hà Huy - 21127296" << endl;
	GotoXY(x, y + 3);
	wcout << L"Quách Tấn Dũng - 21127247" << endl;
	GotoXY(x, y + 4);
	wcout << L"Nguyễn Cát Huy - 21127300" << endl;
	GotoXY(x, y + 5);
	wcout << L"Press Enter to return to menu" << endl;
}

void Game::startGame() {
	setUp();

	MainMenu m;
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
	case OPTIONS::CREDIT:
	{
		ClearBackground();
		printCredit(this->bufferWidth / 2, this->bufferHeight / 2);
		int key;
		do {
			key = toupper(_getch());
		} while (key != ENTER_KEY);
		goto menu;
		break;
	}
	case OPTIONS::EXIT:
		ClearBackground();
		return;
		break;
	}

	ClearBackground();
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