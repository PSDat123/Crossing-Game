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

//void soundThread(bool* isRunning, bool* isPause) {
	//bool sound_menu = PlaySound(_T("Sound/menu_music.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
//}

void fastIO(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}

void Game::setUp() {
	MoveConsole(100, 0);
	ChangeConsoleFontSize(18);
	SetConsoleSize(this->bufferWidth, this->bufferHeight);
	SetConsoleOutputCP(CP_UTF8);
	SetColor(240);
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

void printCredit(int x, int y) {
	GotoXY(x, y++);
	wcout << L"███████████████████████████████╗";
	GotoXY(x, y++);
	wcout << L"█                             █║";
	GotoXY(x, y++);
	wcout << L"█       Made by Group 1       █║" << endl;
	GotoXY(x, y++);;
	wcout << L"█  Phùng Siêu Đạt - 21127243  █║" << endl;
	GotoXY(x, y++);
	wcout << L"█  Đặng Hà Huy    - 21127296  █║" << endl;
	GotoXY(x, y++);
	wcout << L"█  Quách Tấn Dũng - 21127247  █║" << endl;
	GotoXY(x, y++);
	wcout << L"█  Nguyễn Cát Huy - 21127300  █║" << endl;
	GotoXY(x, y++);
	wcout << L"█                             █║";
	GotoXY(x, y++);
	wcout << L"███████████████████████████████║";
	GotoXY(x, y++);
	wcout << L"╚══════════════════════════════╝";
	GotoXY(x, y);
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
	case OPTIONS::CREDIT:{
		ClearBackground();
		printCredit((this->bufferWidth / 2) - 16, (this->bufferHeight / 2) - 5);

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