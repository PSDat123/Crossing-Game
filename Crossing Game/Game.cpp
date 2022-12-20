#include "Game.h"

Game::Game(Console* screen) {
	isPaused = false;
	state = GAMESTATE::RUNNING;
	console = screen;
	console->GetConsoleSize(width, height);
	character = People(0, 0, { 0, 0, SHORT(width - 1), SHORT(height - 1) });
}

void Game::restartGame() {
	string name = character.getName();
	character = People(0, 0, { 0, 0, SHORT(width - 1), SHORT(height - 1) });
	character.setName(&name[0]);
	level = 1;
	score = 0;
}

void Game::saveGame() {
	string filename = string(character.getName()) + ".sav";
	string dir = "./Save";
	CreateDirectoryW(L"./Save", NULL);
	ofstream saveFile(dir + "/" + filename, ios::binary);
	if (saveFile.is_open()) {
		time_t s = time(nullptr);
		saveFile.write((char*)&s, sizeof(time_t));
		saveFile.write(character.getName(), MAX_NAME_LENGTH);
		int life = character.getLife();
		saveFile.write((char*)&life, sizeof(life));
		saveFile.write((char*)&level, sizeof(level));
		saveFile.write((char*)&score, sizeof(score));
		saveFile.write((char*)&highScore, sizeof(highScore));
	}
	saveFile.close();
}

void gameOverThread(Game* g, bool* isRunning, int* curSelected, int* prevSelected) {
	g->restartGame();
	int x = (g->width / 2) - 15, y = (g->height / 2) - 5, optionY = y + 4;
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

void pausedThread(Game* g, bool* isRunning, int* curSelected, int* prevSelected) {
	int x = (g->width / 2) - 15, y = (g->height / 2) - 5, optionY = y + 4;
	g->console->DrawString(L"████████████████████████████╗", x, y++);
	g->console->DrawString(L"█                          █║", x, y++);
	g->console->DrawString(L"█          PAUSED          █║", x, y++);
	g->console->DrawString(L"█                          █║", x, y++);
	g->console->DrawString(L"█        Resume            █║", x, y++);
	g->console->DrawString(L"█        Restart           █║", x, y++);
	g->console->DrawString(L"█        Return to menu    █║", x, y++);
	g->console->DrawString(L"█        Save game         █║", x, y++);
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

void settingThread(Game* g, bool* isRunning, int* curSelected, int* prevSelected) {
	int sX = g->width / 2, sY = g->height / 2 - 3;
	g->console->DrawString(L"█████████████████████████████████████████████████╗", sX - 25, sY++);
	g->console->DrawString(L"█                                               █║", sX - 25, sY++);
	g->console->DrawString(L"█   Background music:    On                     █║", sX - 25, sY++);
	g->console->DrawString(L"█                        Off                    █║", sX - 25, sY++);
	g->console->DrawString(L"█   Press Enter to select and go back to menu   █║", sX - 25, sY++);
	g->console->DrawString(L"█                                               █║", sX - 25, sY++);
	g->console->DrawString(L"█████████████████████████████████████████████████║", sX - 25, sY++);
	g->console->DrawString(L"╚════════════════════════════════════════════════╝", sX - 25, sY++);
	g->console->DrawString(L"►", sX - 2, sY + *curSelected - 6);							
	do {
		if (*curSelected != *prevSelected) {
			g->console->DrawString(L" ", sX - 2, sY + *prevSelected - 6);
			g->console->DrawString(L"►", sX - 2, sY + *curSelected - 6);
			*prevSelected = *curSelected;
		}
		g->console->UpdateScreen();
		this_thread::sleep_for(chrono::milliseconds(INTERVAL));
	} while (*isRunning);
	if (g->state == GAMESTATE::SETTING) {
		if (*curSelected == 0) g->soundOn = true;
		else g->soundOn = false;
	}
}

void gameThread(Game* g) {
	srand(static_cast<unsigned int>(time(NULL)));
startGame:
	Map map(g->width, g->height, 5, &g->character, &g->level, &g->score);
	map.drawOutline(g->console);
	map.resetCharacter();
	g->character.draw(g->console);
	do{
		if (g->isPaused) {
			bool isRunning = true;
			int  prevSelected = 0, curSelected = 0;
			vector<OPTIONS> options = { OPTIONS::RESUME, OPTIONS::RESTART, OPTIONS::RETURN, OPTIONS::SAVE_GAME, OPTIONS::EXIT };
			thread t(pausedThread, g, &isRunning, &curSelected, &prevSelected);
			g->key = 0;
			do {
				if (g->key == UP_ARROW || g->key == W) {
					prevSelected = curSelected;
					curSelected--;
					if (curSelected == -1) {
						curSelected = options.size() - 1;
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
				if (g->key == ESC) {
					prevSelected = curSelected;
					curSelected = 0;
					break;
				}
				this_thread::sleep_for(chrono::milliseconds(INTERVAL));
			} while (g->key != ENTER_KEY);
			isRunning = false;
			t.join();
			g->console->ClearBackground();
			g->isPaused = false;

			switch (options[curSelected]) {
			case OPTIONS::RESTART:
				goto startGame;
				break;
			case OPTIONS::SAVE_GAME:
				g->saveGame();
			case OPTIONS::RESUME:
				map.drawOutline(g->console);
				map.drawMain(g->console);
				break;
			case OPTIONS::RETURN:
				g->state = GAMESTATE::MENUING;
				return;
			case OPTIONS::EXIT:
				g->state = GAMESTATE::EXITED;
				return;
			}
		}

		map.updateMain(g->console);
		map.drawMain(g->console);

		if (!g->character.isDead()) {
			g->character.draw(g->console);
			g->character.update();
		}
		else {
			// Game over
			mciSendString(L"play Sound/game_over.wav from 0 to 1000", NULL, 0, NULL);
			g->isGameover = true;
			bool isRunning = true;
			int  prevSelected = 0, curSelected = 0;
			vector<OPTIONS> options = { OPTIONS::RESTART, OPTIONS::RETURN, OPTIONS::EXIT };
			thread t(gameOverThread, g, &isRunning, &curSelected, &prevSelected);
			g->key = 0;
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
				if (g->key == ESC) {
					prevSelected = curSelected;
					curSelected = options.size() - 1;
					break;
				}
				this_thread::sleep_for(chrono::milliseconds(INTERVAL));
			} while (g->key != ENTER_KEY);
			isRunning = false;
			t.join();
			g->console->ClearBackground();
			g->console->UpdateScreen();
			g->isGameover = false;

			if (options[curSelected] == OPTIONS::RESTART) {
				goto startGame;
			}
			else if(options[curSelected] == OPTIONS::RETURN) {
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
			if (g->score > g->highScore) g->highScore = g->score;
			g->level += 1;
			g->character.addLife(1);
			map.drawLevelText(g->console);
			map.drawLiveText(g->console);

			g->isTransition = true;
			map.nextLevel(g->console);
			g->isTransition = false;
		}

		if (map.checkCollision(&g->character)) {
			g->character.removeLife(1);
			map.drawLiveText(g->console);
			//Play death animation
			mciSendString(L"play Sound/death.mp3 from 300 to 600", NULL, 0, NULL);
			g->character.erase(g->console);
			map.resetCharacter();
		}

		g->console->UpdateScreen();
		this_thread::sleep_for(chrono::milliseconds(INTERVAL));
	} while (g->state == GAMESTATE::RUNNING);
}

vector<wstring> getSaveFiles(wstring folder){
	vector<wstring> names;
	wstring search_path = folder + L"/*.sav";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

void loadGameThread(Game* g, bool* isRunning, int* curSelected, int* prevSelected, int* numSaves) {
	wstring path = L"./Save";
	vector<wstring> files = getSaveFiles(path);
	if (!files.size()) {
		int x = (g->width - 52) / 2, y = g->height / 2;
		g->console->ClearBackground();
		g->console->DrawHorizontalLine(L'█', x - 3, x + 53, y - 2);
		g->console->DrawVerticalLine(L'█', x - 3, y - 2, y + 2);
		g->console->DrawString(L"No save file available! Press ESC to return to menu.", x, y);
		g->console->DrawHorizontalLine(L'█', x - 3, x + 53, y + 2);
		g->console->DrawVerticalLine(L'█', x + 53, y - 2, y + 2);
		g->console->DrawChar(L'╗', x + 54, y - 2);
		g->console->DrawVerticalLine(L'║', x + 54, y - 1, y + 2);
		g->console->DrawChar(L'╝', x + 54, y + 3);
		g->console->DrawHorizontalLine(L'═', x - 2, x + 53, y + 3);
		g->console->DrawChar(L'╚', x - 3, y + 3);
		g->console->UpdateScreen();
		*isRunning = false;
		return;
	}
	struct Save {
		time_t timestamp;
		char name[MAX_NAME_LENGTH];
		int life;
		int level;
		int score;
		int highscore;
	};
	vector<Save> allSaves;
	Save curSave;
	int maxfile = (g->height - 5) / 7;
	if (files.size() <= maxfile) maxfile = files.size();
	g->console->ClearBackground();
	
	for (int i = 0; i < files.size(); ++i) {
		ifstream fin(path + L"/" + files[i], ios::binary);
		if (fin.is_open()) {
			fin.read((char*)&curSave.timestamp, sizeof(time_t));
			fin.read((char*)&curSave.name, MAX_NAME_LENGTH);
			fin.read((char*)&curSave.life, sizeof(int));
			fin.read((char*)&curSave.level, sizeof(int));
			fin.read((char*)&curSave.score, sizeof(int));
			fin.read((char*)&curSave.highscore, sizeof(int));
			*numSaves = *numSaves + 1;
			allSaves.push_back(curSave);	
		}
		else {
			--i;
		}
		fin.close();	
	}
	for (int i = 1; i < allSaves.size(); ++i) {
		Save s = allSaves[i];
		int j = i - 1;
		while (j >= 0 && allSaves[j].timestamp < s.timestamp) {
			allSaves[j + 1] = allSaves[j];
			--j;
		}
		allSaves[j + 1] = s;
	}

	for(int i = 0; i < maxfile; ++i){
		Save curSave = allSaves[i];
		struct tm dt;
		char t[30];
		localtime_s(&dt, &curSave.timestamp);
		strftime(t, sizeof(t), "%H:%M:%S %d/%m/%y", &dt);
		wstring timestamp = wstring(t, t + strlen(t));
		int y = 7 * i + 5, x = g->width / 2 - 32, namelength = strlen(curSave.name);
		g->console->DrawHorizontalLine(L'█', x, g->width - x, y);
		g->console->DrawChar(L'╗', g->width - x + 1, y);
		g->console->DrawVerticalLine(L'║', g->width - x + 1, y + 1, y + 6);
		g->console->DrawChar(L'╝', g->width - x + 1, y + 6);
		g->console->DrawHorizontalLine(L'═', x + 1, g->width - x, y + 6);
		g->console->DrawChar(L'╚', x, y + 6);
		g->console->DrawVerticalLine(L'█', x, y, y + 5);
		g->console->DrawVerticalLine(L'█', g->width - x, y, y + 5);
		g->console->DrawHorizontalLine(L'█', x, g->width - x, y + 5);

		g->console->DrawString(wstring(curSave.name, curSave.name + namelength), x + 5, y + 2);
		g->console->DrawString(L"Life: " + to_wstring(curSave.life), x + MAX_NAME_LENGTH + 9, y + 2);
		g->console->DrawString(L"Level: " + to_wstring(curSave.level), x + MAX_NAME_LENGTH + 29, y + 2);
		g->console->DrawString(L"Score: " + to_wstring(curSave.score), x + 5, y + 3);
		g->console->DrawString(L"High Score: " + to_wstring(curSave.highscore), x + MAX_NAME_LENGTH + 9, y + 3);
		g->console->DrawString(timestamp, x + MAX_NAME_LENGTH + 29, y + 3);
	}
	g->console->UpdateScreen();
	int x = g->width / 2 - 35, y = 7;
	g->console->DrawString(L"► ", x, y  + *curSelected * 7);
	do {
		if (*curSelected != *prevSelected) {
			g->console->DrawString(L"  ", x, y + *prevSelected * 7);
			g->console->DrawString(L"► ", x, y + *curSelected * 7);
			*prevSelected = *curSelected;
		}
		g->console->UpdateScreen();
		this_thread::sleep_for(chrono::milliseconds(INTERVAL));
	} while (*isRunning);
	if (g->state != GAMESTATE::LOADING) return;
	g->character.setName(allSaves[*curSelected].name);
	g->character.setLife(allSaves[*curSelected].life);
	g->level = allSaves[*curSelected].level;
	g->score = allSaves[*curSelected].score;
	g->highScore = allSaves[*curSelected].highscore;
}

void Game::continueGame() {
	wstring path = L"./Save";
	vector<wstring> files = getSaveFiles(path);
	struct Save {
		time_t timestamp;
		char name[MAX_NAME_LENGTH];
		int life;
		int level;
		int score;
		int highscore;
	};
	Save curSave;
	int maxSave = -1;
	long long maxTime = 0;
	for (int i = 0; i < files.size(); ++i) {
		ifstream fin(path + L"/" + files[i], ios::binary);
		if (fin.is_open()) {
			fin.read((char*)&curSave.timestamp, sizeof(time_t));
			if (curSave.timestamp > maxTime) {
				maxTime = curSave.timestamp;
				maxSave = i;
			}
		}
		fin.close();
	}
	if (maxSave == -1) return;
	wstring filename = path + L'/' + files[maxSave];
	ifstream fin(filename, ios::binary);
	if (fin.is_open()) {
		fin.read((char*)&curSave.timestamp, sizeof(time_t));
		fin.read((char*)&curSave.name, MAX_NAME_LENGTH);
		fin.read((char*)&curSave.life, sizeof(int));
		fin.read((char*)&curSave.level, sizeof(int));
		fin.read((char*)&curSave.score, sizeof(int));
		fin.read((char*)&curSave.highscore, sizeof(int));
	}
	fin.close();
	character.setName(curSave.name);
	character.setLife(curSave.life);
	level = curSave.level;
	score = curSave.score;
	highScore = curSave.highscore;
}

void Game::newGame() {
	int x = (width - 37) / 2, y = height / 2;
	console->ClearBackground();
inputname:
	console->GotoXY(x + 21, y);
	console->DrawHorizontalLine(L'█', x - 3, x + 38, y - 2);
	console->DrawVerticalLine(L'█', x - 3, y - 2, y + 2);
	console->DrawString(L"Input player's name: ", x, y);
	console->DrawHorizontalLine(L'█', x - 3, x + 38, y + 2);
	console->DrawVerticalLine(L'█', x + 38, y - 2, y + 2);

	console->DrawChar(L'╗', x + 39, y - 2);
	console->DrawVerticalLine(L'║', x + 39, y - 1, y + 2);
	console->DrawChar(L'╝', x + 39, y + 3);
	console->DrawHorizontalLine(L'═', x - 3, x + 38, y + 3);
	console->DrawChar(L'╚', x - 3, y + 3);
	console->UpdateScreen();

	restartGame();
	string tempName;
	while (getline(cin, tempName)) {
		if (!tempName.size()) continue;
		if (tempName.size() < MAX_NAME_LENGTH) {
			character.setName(&tempName[0]);
			break;
		}
		console->ClearBackground();
		console->DrawString(L"Name must be less than " + to_wstring(MAX_NAME_LENGTH) + L" characters!", x, y + 1);
		goto inputname;
	}
	console->GotoXY(0, 0);

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

void Game::playSound(bool soundOn) {
	if (!soundOn) {
		mciSendStringA(LPCSTR("pause bgm"), NULL, 0, NULL);
		return;
	}
	mciSendString(L"open \"Sound/background_music.wav \" type mpegvideo alias bgm", NULL, 0, NULL);
	mciSendStringA(LPCSTR("play bgm repeat"), NULL, 0, NULL);
	mciSendString(L"setaudio bgm volume to 50", NULL, 0, NULL);
}

void Game::startGame() {
	MainMenu m(console);
menu:
	playSound(soundOn);
	state = GAMESTATE::MENUING;
	OPTIONS opt = m.runMenu();
	switch (opt) {
	case OPTIONS::CONTINUE: {
		continueGame();
		break;
	}
	case OPTIONS::NEW_GAME: {
		newGame();
		break;
	}
	case OPTIONS::LOAD_GAME: {
		bool isRunning = true;
		state = GAMESTATE::LOADING;
		int curSelected = 0, prevSelected = 0, numSaves = 0, key;
		thread loadThread(loadGameThread, this, &isRunning, &curSelected, &prevSelected, &numSaves);
		do {
			key = toupper(_getch());
			if(key == 224) key = toupper(_getch());
			if (key == UP_ARROW || key == W) {
				prevSelected = curSelected;
				curSelected--;
				if (curSelected == -1) {
					curSelected = numSaves - 1;
				}
			}
			if (key == DOWN_ARROW || key == S) {
				prevSelected = curSelected;
				curSelected++;
				if (curSelected == numSaves) {
					curSelected = 0;
				}
				key = 0;
			}
			if (key == ESC) {
				state = GAMESTATE::MENUING;
				break;
			}
			this_thread::sleep_for(chrono::milliseconds(INTERVAL));
		} while (key != ENTER_KEY);
		isRunning = false;
		loadThread.join();
		if (state == GAMESTATE::MENUING) goto menu;
		break;
	}
	case OPTIONS::SETTINGS: {
		console->ClearBackground();
		int curSelected = 0, prevSelected = 0, key;
		bool isRunning = true;
		this->state = GAMESTATE::SETTING;
		thread set(settingThread, this, &isRunning, &curSelected, &prevSelected);
		do {
			key = toupper(_getch());
			if (key == 224) key = toupper(_getch());
			if (key == UP_ARROW || key == W) {
				prevSelected = curSelected;
				curSelected--;
				if (curSelected == -1) {
					curSelected = 1;
				}
			}
			if (key == DOWN_ARROW || key == S) {
				prevSelected = curSelected;
				curSelected++;
				if (curSelected == 2) {
					curSelected = 0;
				}
				key = 0;
			}
			if (key == ESC) {
				state = GAMESTATE::MENUING;
				break;
			}
			this_thread::sleep_for(chrono::milliseconds(INTERVAL));
		} while (key != ENTER_KEY);
		isRunning = false;
		set.join();
		state == GAMESTATE::MENUING;
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
	}

	console->ClearBackground();
	state = GAMESTATE::RUNNING;
	thread t1(gameThread, this);
	while (state == GAMESTATE::RUNNING) {
		key = toupper(_getch());
		if (key == 224) key = toupper(_getch());
		if (isTransition) continue;
		if (!isGameover && !isPaused) {
			if (key == UP_ARROW ||key == W) {
				this->character.move(DIRECTION::UP);
			}
			else if (key == DOWN_ARROW || key == S) {
				this->character.move(DIRECTION::DOWN);
			}
			else if (key == LEFT_ARROW || key == A) {
				this->character.move(DIRECTION::LEFT);
			}
			else if (key == RIGHT_ARROW || key == D) {
				this->character.move(DIRECTION::RIGHT);
			}
		}
		if (key == ESC) {
			if (!isPaused) {
				isPaused = true;
			}
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	t1.join();
	if (state == GAMESTATE::MENUING) goto menu;
	console->ClearBackground();
	console->UpdateScreen();
	return;
}

Game::~Game() {}