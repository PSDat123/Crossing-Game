#include "Game.h"

Game::Game() {
	this->bufferWidth = 140;
	this->bufferHeight = 50;
	this->isPaused = false;
	this->isRunning = true;
}

void backgroundThread(Game* game, bool* isRunning, bool* isPaused) {
	while (*isRunning) {
		Sleep(30);
	}
}

void soundThread(Game* game, bool* isRunning, bool* isPause) {

}

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
	system("cls");
	isRunning = false;
	t->join();
}

int printCredit() {
	int key = 0;
	do {
		key = toupper(_getch());
		cout << "Made by Group 1: " << endl;
		cout << "Phùng Siêu Đạt - 21127" << endl;
		cout << "Đặng Hà Huy - 21127296" << endl;
		cout << "Quách Tấn Dũng - 21127" << endl;
		cout << "Nguyễn Cát Huy - 21127" << endl;
		cout << "Press Enter to return to menu" << endl;
	} while (key != ENTER_KEY);
	return key;
}

void Game::startGame() {
	setUp();
	isRunning = true;
	isPaused = false;

	MainMenu m;
	OPTIONS opt = m.runMenu();
	
	/*switch (opt) {
	case OPTIONS::CONTINUE:
		break;
	case OPTIONS::NEW_GAME:
		break;
	case OPTIONS::LOAD_GAME:
		break;
	case OPTIONS::SETTINGS:
		break;
	case OPTIONS::CREDIT:
		//ClearBackground();
		//int key = printCredit();
		//if (key == ENTER_KEY) {}
		break;
	case OPTIONS::EXIT:
		//exitGame();
		//break;
	}*/

	//thread t1(backgroundThread, this, &isRunning, &isPaused);
	while (true) {
		int keyInput = toupper(_getch());

		if (keyInput == 27) {
			/*exitGame(&t1);*/
			return;
		}
	}
}

Game::~Game() {}