#pragma once
#pragma execution_character_set( "utf-8" )
#include "Console.h"
#include "People.h"
#include "Macro.h"
#include "Map.h"
#include "MainMenu.h"

class Game {
public:
	Game(Console*);
	~Game();

	void startGame();
	void saveGame();

	void loadGame();
	void loadGameFile(string file);

	void pauseGame();
	void resumeGame();

	void exitGame();
	void restartGame();
	void printCredit(int, int);

	friend void gameThread(Game* g);
	friend void gameOverThread(Game* g, bool* isRunning, int*, int*);
private:
	Console* console;
	SHORT width, height;
	bool isGameover = false, isPaused, isTransition = false;
	GAMESTATE state;
	People character;
	int level = 1, key = 0;
	int score = 0, highScore = 0;
};
