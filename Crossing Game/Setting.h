#pragma once
#include "Macro.h"
#include "Console.h"

class Setting {
public:
	Setting(Console*);
	~Setting();

	SETTING runSetting();
	friend void settingThread(Setting*);
private:
	bool isRunning;
	int curSelected, prevSelected;
	SHORT width, height;
	vector<pair<SETTING, wstring>> options;
	Console* console;
};