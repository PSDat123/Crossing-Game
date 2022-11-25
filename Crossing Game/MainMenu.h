#pragma once
#include "Console.h"
#include "Vehicle.h"
#include "Macro.h"

class MainMenu {
public:
	MainMenu(Console*);
	~MainMenu();
	OPTIONS runMenu();
	 
	friend void menuThread(MainMenu* m);
private:
	vector<pair<OPTIONS, wstring>> options;
	vector<wstring> title;
	int curSelected, prevSelected;
	bool isRunning;
	void printTitle(int, int);
	Console* console;
};
