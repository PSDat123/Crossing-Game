#include "Game.h"

Game::Game(Console* screen) {
	isPaused = false;
	state = GAMESTATE::RUNNING;
	console = screen;
	console->GetConsoleSize(width, height);
	character = People(0, 0, {0, 0, SHORT(width - 1), SHORT(height - 1)});
}

void Game::restartGame() {
	character = People(0, 0, { 0, 0, SHORT(width - 1), SHORT(height - 1) });
	level = 1;
	score = 0;
}

void gameOverThread(Game* g, bool* isRunning, int* curSelected, int* prevSelected) {
	g->restartGame();
	int x = (g->width / 2) - 15, y = (g->height / 2) - 5;
	int optionY = y + 4;
	g->console->DrawString(L"████████████████████████████╗", x, y++);
	g->console->DrawString(L"█                          █║", x, y++);
	g->console->DrawString(L"█        GAME OVER!        █║", x, y++);
	g->console->DrawString(L"█                          █║", x, y++);
	g->console->DrawString(L"█        Restart           █║", x, y++);
	g->console->DrawString(L"█        Return to menu    █║", x, y++);
	g->console->DrawString(L"█        Exit game         █║", x, y++);
	g->console->DrawString(L"█                          █║", x, y++);
	g->console->DrawString(L"█                          █║", x, y++);
	g->console->DrawString(L"████████████████████████████║", x, y++);
	g->console->DrawString(L"╚═══════════════════════════╝", x, y++);
	g->console->DrawString(L"► ", x + 5, optionY + *curSelected);
	g->console->UpdateScreen();

	do {
		if (*curSelected != *prevSelected) {
			g->console->DrawString(L"  ", x + 5, optionY + *prevSelected);
			g->console->DrawString(L"► ", x + 5, optionY + *curSelected);
			*prevSelected = *curSelected;
		}
		g->console->UpdateScreen();

		this_thread::sleep_for(chrono::milliseconds(INTERVAL));
	} while (*isRunning);
}


void gameThread(Game* g) {
	srand(static_cast<unsigned int>(time(NULL)));
startGame:
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
			// Game over
			g->isGameover = true;
			bool isRunning = true;
			int  prevSelected = 0, curSelected = 0;
			vector<string> options = { "Restart", "Return", "Exit"};
			thread t(gameOverThread, g, &isRunning, &curSelected, &prevSelected);
			do {
				if (g->key == UP_ARROW || g->key == W) {
					prevSelected = curSelected;
					curSelected--;
					if (curSelected == -1) {
						curSelected = (int)options.size() - 1;
					}
					g->key = 0;
				}
				if (g->key == DOWN_ARROW || g->key == S) {
					prevSelected = curSelected;
					curSelected++;
					if (curSelected == options.size()) {
						curSelected = 0;
					}
					g->key = 0;
				}
				this_thread::sleep_for(chrono::milliseconds(INTERVAL));
			} while (g->key != ENTER_KEY);
			isRunning = false;
			t.join();
			g->console->ClearBackground();
			g->console->UpdateScreen();
			g->isGameover = false;

			if (options[curSelected] == "Restart") {
				goto startGame;
			}
			else if(options[curSelected] == "Return") {
				g->state = GAMESTATE::MENUING;
				return;
			}
			else {
				g->state = GAMESTATE::EXITED;
				return;

			}
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
	} while (g->state == GAMESTATE::RUNNING);
}

void settingThread(Game* g) {

}

void loadGameThread(Game* g) {

}


void Game::exitGame() {
	console->ClearBackground();
	console->UpdateScreen();
	state = GAMESTATE::EXITED;
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
	case OPTIONS::CONTINUE: {
		break;
	}
	case OPTIONS::NEW_GAME: {
		break;
	}
	case OPTIONS::LOAD_GAME: {
		state = GAMESTATE::MENUING;
		do {

		} while (state == GAMESTATE::MENUING);
		break;
	}
	case OPTIONS::SETTINGS: {
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
	state = GAMESTATE::RUNNING;
	thread t1(gameThread, this);
	while (state == GAMESTATE::RUNNING) {
		key = toupper(_getch());
		if (isTransition) continue;
		if (key == W) {
			if(!isGameover) 
				this->character.move(DIRECTION::UP);
		}
		else if (key == S) {
			if (!isGameover)
				this->character.move(DIRECTION::DOWN);
		}
		else if (key == A) {
			if (!isGameover)
				this->character.move(DIRECTION::LEFT);
		}
		else if (key == D) {
			
				this->character.move(DIRECTION::RIGHT);
		}
		if (key == ESC) {
			if (!isGameover)
				exitGame();
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	t1.join();
	if (state == GAMESTATE::MENUING) {
		goto menu;
	}
	return;
}

Game::~Game() {}