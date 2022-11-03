#pragma once
#pragma execution_character_set( "utf-8" )
#include "Console.h"
#include "People.h"
using namespace std;

class Game {
public:
	//Game();
	//~Game();
	void startGame();
	void exitGame();
	void drawGame();
	void saveGame();
	void loadGame();
	void pauseGame();
	void resumeGame();
	void exitGame(thread*);
private:
	bool isRunning, isPaused;
	SHORT bufferWidth, bufferHeight;
};