#pragma once
#include "Console.h"
#include "Macro.h"
#include "Vehicle.h"
#include "Animal.h"

class MainMenu {
public:
	MainMenu();
	~MainMenu();
	OPTIONS runMenu();
	
	friend void menuThread(MainMenu* m);
private:
	vector<pair<OPTIONS, wstring>> options;
	vector<wstring> title;
	int curSelected, prevSelected;
	bool isRunning;
	void printTitle(int, int);
};
