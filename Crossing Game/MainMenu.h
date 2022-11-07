#pragma once
#include <vector>
#include "Console.h"
#include "Macro.h"
#include "Vehicle.h"
using namespace std;

enum class OPTIONS{
	CONTINUE ,
	NEW_GAME,
	LOAD_GAME,
	SETTINGS,
	CREDIT,
	EXIT
};

class MainMenu {
public:
	MainMenu();
	~MainMenu();
	OPTIONS runMenu();
	
	friend void menuThread(MainMenu* m);
private:
	vector<OPTIONS> options;
	vector<string> title;
	int titleSize;
	int curSelected, prevSelected;
	bool isRunning;
	void printTitle(int, int);
};
