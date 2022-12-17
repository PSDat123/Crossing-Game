#pragma once
#include "Console.h"
#include "People.h"
#include "Map.h"
#include "MainMenu.h"

class Game {
public:
	Game(Console*);
	~Game();

	void startGame();
	void saveGame();
	void continueGame();
	void newGame();

	void exitGame();
	void restartGame();
	void printCredit(int, int);
	void playSound(bool soundOn);

	friend void gameThread(Game* g);
	friend void gameOverThread(Game* g, bool* isRunning, int*, int*);
	friend void pausedThread(Game* g, bool* isPausing, int*, int*);
	friend void loadGameThread(Game* g, bool* isRunning, int*, int*, int*);
	friend void settingThread(Game* g, bool* isRunning, int*, int*);
private:
	Console* console;
	SHORT width, height;
	bool isGameover = false, isPaused, isTransition = false, soundOn = true;
	GAMESTATE state;
	People character;
	int level = 1, key = 0;
	int score = 0, highScore = 0;
};
