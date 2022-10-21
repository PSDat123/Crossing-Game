#pragma once
#include <Windows.h>
#include "People.h"
using namespace std;

class Game {
public:
	Game();
	~Game();
	void startGame();
	void exitGame();
	void drawGame();
	void saveGame();
	void loadGame();
	void pauseGame();
	void resumeGame();
	void exitGame(HANDLE);
private
};