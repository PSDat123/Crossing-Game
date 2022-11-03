#include "Game.h"

void Game::exitGame(thread* t) {
	system("cls");
	isRunning = false;
	t->join();
}

void backgroundThread(Game* game, bool* isRunning, bool* isPaused) {
	while (*isRunning) {
		ClearBackground();
		//GotoXY(7,10);
		//cout << " ██████╗██████╗  ██████╗ ███████╗███████╗██╗███╗   ██╗ ██████╗      ██████╗  █████╗ ███╗   ███╗███████╗";
		//GotoXY(7, 11);
		//cout << "██╔════╝██╔══██╗██╔═══██╗██╔════╝██╔════╝██║████╗  ██║██╔════╝     ██╔════╝ ██╔══██╗████╗ ████║██╔════╝";
		//GotoXY(7, 12);
		//cout << "██║     ██████╔╝██║   ██║███████╗███████╗██║██╔██╗ ██║██║  ███╗    ██║  ███╗███████║██╔████╔██║█████╗  ";
		//GotoXY(7, 13);
		//cout << "██║     ██╔══██╗██║   ██║╚════██║╚════██║██║██║╚██╗██║██║   ██║    ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ";
		//GotoXY(7, 14);
		//cout << "╚██████╗██║  ██║╚██████╔╝███████║███████║██║██║ ╚████║╚██████╔╝    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗";
		//GotoXY(7, 15);
		//cout << " ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝╚═╝╚═╝  ╚═══╝ ╚═════╝      ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝";
		//
		cout << R"(
 ▄▄· ▄▄▄        .▄▄ · .▄▄ · ▪   ▐ ▄  ▄▄ •      ▄▄ •  ▄▄▄· • ▌ ▄ ·. ▄▄▄ .
▐█ ▌▪▀▄ █·▪     ▐█ ▀. ▐█ ▀. ██ •█▌▐█▐█ ▀ ▪    ▐█ ▀ ▪▐█ ▀█ ·██ ▐███▪▀▄.▀·
██ ▄▄▐▀▀▄  ▄█▀▄ ▄▀▀▀█▄▄▀▀▀█▄▐█·▐█▐▐▌▄█ ▀█▄    ▄█ ▀█▄▄█▀▀█ ▐█ ▌▐▌▐█·▐▀▀▪▄
▐███▌▐█•█▌▐█▌.▐▌▐█▄▪▐█▐█▄▪▐█▐█▌██▐█▌▐█▄▪▐█    ▐█▄▪▐█▐█ ▪▐▌██ ██▌▐█▌▐█▄▄▌
·▀▀▀ .▀  ▀ ▀█▄▀▪ ▀▀▀▀  ▀▀▀▀ ▀▀▀▀▀ █▪·▀▀▀▀     ·▀▀▀▀  ▀  ▀ ▀▀  █▪▀▀▀ ▀▀▀ 
)";

		Sleep(30);
	}
}

void Game::startGame() {
	bufferWidth = 200;
	bufferHeight = 60;
	MoveConsole(150, 0);
	//ChangeConsoleFontSize(12);
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
	thread t1(backgroundThread, this, &isRunning, &isPaused);
	while (true) {
		int keyInput = toupper(_getch());

		if (keyInput == 27) {
			exitGame(&t1);
			return;
		}
	}
}
