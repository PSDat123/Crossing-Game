#include "Setting.h"

Setting::Setting(Console* screen) {
	this->isRunning = false;
	this->console = screen;
	this->prevSelected = 0;
	this->curSelected = 0;
	this->options = {
		{SETTING::SOUND_ON, L"On"},
		{SETTING::SOUND_OFF, L"Off"}
	};
	this->console->GetConsoleSize(width, height);
}

void settingThread(Setting* s) {
	SHORT sX = s->width / 2, sY = s->height / 2;
	s->console->DrawString(L"Background music:  ► On", sX, sY);
	s->console->DrawString(L"                     Off", sX, sY - 1);
	s->console->DrawString(L"Press Enter to select and Enter again to go back to menu", sX, sY - 2);
	do {
		if (s->curSelected != s->prevSelected) {
			s->console->DrawString(L" ", sX, sY);
			s->console->DrawString(L"►", sX, sY);
			s->prevSelected = s->curSelected;
		}
		s->console->UpdateScreen();
	} while (s->isRunning);
}

SETTING Setting::runSetting() {
	int key = 0;
	this->console->ClearBackground();
	this->isRunning = true;
	thread t(settingThread, this);
	//mciSendString(_T("open \"Sound/button.wav\" type mpegvideo alias button"), NULL, 0, NULL);
	do {
		key = toupper(_getch());
		if (key == UP_ARROW || key == W) {
			//mciSendStringA(LPCSTR("play button from 1000"), NULL, 0, NULL);
			prevSelected = curSelected;
			curSelected--;
			if (curSelected == -1) {
				curSelected = (int)options.size() - 1;
			}
		}
		if (key == DOWN_ARROW || key == S) {
			//mciSendStringA(LPCSTR("play button from 1000"), NULL, 0, NULL);
			prevSelected = curSelected;
			curSelected++;
			if (curSelected == options.size()) {
				curSelected = 0;
			}
		}
	} while (key != ENTER_KEY);
	this->isRunning = false;
	t.join();
	return this->options[this->curSelected].first;
}

Setting::~Setting() {}