﻿#include "Game.h"

Game::Game(Console* screen) {
	isPaused = false;
	isRunning = true;
	console = screen;
	console->GetConsoleSize(width, height);
	character = People(0, 0, { 0, 0, SHORT(width - 1), SHORT(height - 1) });
}

void gameThread(Game* g) {
	srand(static_cast<unsigned int>(time(NULL)));
	Map map(g->width, g->height, 5, &g->character, &g->level, &g->score);
	map.drawOutline(g->console);
	map.resetCharacter();
	g->character.draw(g->console);
	do{
		map.updateMain(g->console);
		map.drawMain(g->console);
		if (!g->character.isDead()) {
			g->character.draw(g->console);
			g->character.update();
		}
		else {
			// Game over!
		}

		if (map.updateScore()) {
			map.drawScoreText(g->console);
		}

		if (map.checkFinished(&g->character)) {
			map.saveScore();
			g->level += 1;
			map.drawLevelText(g->console);
			g->character.addLife(1);

			g->isTransition = true;
			map.nextLevel(g->console);
			g->isTransition = false;
			//g->isRunning = false;
		}

		if (map.checkCollision(&g->character)) {
			g->character.removeLife(1);
			//Play death animation
			map.resetCharacter();
		}

		g->console->UpdateScreen();

		this_thread::sleep_for(chrono::milliseconds(INTERVAL));
	} while (g->isRunning);
}

void loadGameThread(Game* g) {

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
	mciSendString(_T("open \"Sound/background_music.wav \" type mpegvideo alias bgm"), NULL, 0, NULL);
	mciSendStringA(LPCSTR("play bgm from 0"), NULL, 0, NULL);
menu:
	OPTIONS opt = m.runMenu();
	switch (opt) {
	case OPTIONS::CONTINUE: {
		break;
	}
	case OPTIONS::NEW_GAME: {
		break;
	}
	case OPTIONS::LOAD_GAME: {
		break;
	}
	case OPTIONS::SETTINGS: {
		Setting s(console);
		SETTING set = s.runSetting();
		switch (set) {
		case SETTING::SOUND_ON:
			mciSendStringA(LPCSTR("play bgm"), NULL, 0, NULL);
			break;
		case SETTING::SOUND_OFF:
			mciSendString(_T("pause bgm"), NULL, 0, NULL);
			break;
		}

		int key;
		do {
			key = toupper(_getch());
		} while (key != ENTER_KEY);
		goto menu;
		break;
	}

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
		int key = toupper(_getch());
		if (isTransition) continue;
		if (key == W || key == UP_ARROW) {
			this->character.move(DIRECTION::UP);
		}
		else if (key == S || key == DOWN_ARROW) {
			this->character.move(DIRECTION::DOWN);
		}
		else if (key == A || key == LEFT_ARROW) {
			this->character.move(DIRECTION::LEFT);
		}
		else if (key == D || key == RIGHT_ARROW) {
			this->character.move(DIRECTION::RIGHT);
		}
		if (key == ESC) {
			exitGame(&t1);
			return;
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

Game::~Game() {}