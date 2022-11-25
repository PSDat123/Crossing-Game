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

	void setUp();

	void startGame();

	void drawGame();
	void saveGame();

	void loadGame();
	void loadGameFile(string file);

	void pauseGame();
	void resumeGame();

	void exitGame(thread*);
	friend void gameThread(Game* g);
	friend class MainMenu;
private:
	Console* console;
	SHORT width, height;
	bool isRunning, isPaused;

};

void settings();
void printCredit(int, int);
void fastIO();
void backgroundThread(Game*, bool*, bool*);
void soundThread(Game*, bool*, bool*);