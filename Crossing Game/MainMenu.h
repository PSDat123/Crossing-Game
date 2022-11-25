#pragma once
#include "Macro.h"
#include "Console.h"
#include "Vehicle.h"
#include "Car.h"
#include "Truck.h"

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
