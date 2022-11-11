#pragma once
#pragma execution_character_set( "utf-8" )
#include "Console.h"
#include "Macro.h"
#include "Vehicle.h"

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
