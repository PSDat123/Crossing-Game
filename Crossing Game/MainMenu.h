#pragma once
#include "Macro.h"
#include "Console.h"
#include "Lane.h"

class MainMenu {
public:
	MainMenu(Console*);
	~MainMenu();
	OPTIONS runMenu();
	 
	friend void menuThread(MainMenu* m);
	friend void animateExit(MainMenu* m);
private:
	SHORT width, height;
	vector<pair<OPTIONS, wstring>> options;
	vector<wstring> title;
	int curSelected, prevSelected;
	bool isRunning;
	void printTitle(int, int);
	Console* console;
};
