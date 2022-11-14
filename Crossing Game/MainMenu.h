#pragma once
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
	vector<wstring> title;
	int curSelected, prevSelected;
	bool isRunning;
	void printTitle(int, int);
};
