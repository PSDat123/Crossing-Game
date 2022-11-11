#include "Game.h"

void Game::exitGame(thread* t) {
	system("cls");
	isRunning = false;
	t->join();
}

void backgroundThread(Game* game, bool* isRunning, bool* isPaused) {
	while (*isRunning) {
		Sleep(30);
	}
}

void Game::setUp() {
	this->bufferWidth = 140;
	this->bufferHeight = 50;
	MoveConsole(100, 0);
	ChangeConsoleFontSize(18);
	SetConsoleSize(bufferWidth, bufferHeight);
	SetConsoleOutputCP(CP_UTF8);
	ChangeBackground();
	FixConsoleWindow();
	ShowConsoleCursor(false);
	ClearBackground();
}

void Game::startGame() {
	setUp();

	//int width, height;
	//GetConsoleSize(width, height);
	//cout << width << endl << height;
	isRunning = true;
	isPaused = false;

	MainMenu m;
	OPTIONS opt = m.runMenu();
	
	//switch (opt) {

	//}
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