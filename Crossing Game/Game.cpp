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

void Game::startGame() {
	bufferWidth = 150;
	bufferHeight = 40;
	MoveConsole(150, 0);
	ChangeConsoleFontSize(18);
	SetConsoleSize(bufferWidth, bufferHeight);
	SetScreenBufferSize(bufferWidth, bufferHeight);
	SetConsoleOutputCP(CP_UTF8);
	ChangeBackground();
	FixConsoleWindow();
	ShowConsoleCursor(false);
	ClearBackground();

	int width, height;
	GetConsoleSize(width, height);
	cout << width << endl << height;
	isRunning = true;
	isPaused = false;

	MainMenu m;
	OPTIONS opt = m.runMenu();
	
	//thread t1(backgroundThread, this, &isRunning, &isPaused);
	while (true) {
		int keyInput = toupper(_getch());

		if (keyInput == 27) {
			/*exitGame(&t1);*/
			return;
		}
	}
}
