#pragma once
#include "Macro.h"
using namespace std;

class Console {
public:
	Console();
	~Console();

	void FixConsoleWindow();
	void GotoXY(int, int);
	void ChangeBackgroundColor(int);
	void ClearBackground();
	void ShowConsoleCursor(bool);
	void GetConsoleSize(SHORT& width, SHORT& height);
	void GetMaximumConsoleSize(SHORT& width, SHORT& height);
	void SetConsoleSize(SHORT& width, SHORT& height);
	void MoveConsole(int X, int Y);
	void ChangeConsoleFontSize(SHORT);
	void UpdateScreen();
	void DrawChar(wchar_t c, int x, int y, short col = 240);
	void DrawPixel(int x, int y, short col = 240);
	void DrawString(wstring s, int x, int y, short col = 240);
	void DrawHorizontalLine(wchar_t c, int start_x, int end_x, int y, short col = 240);
	void DrawVerticalLine(wchar_t c, int x, int start_y, int end_y, short col = 240);
	void ShiftUp(SMALL_RECT);
	void ShiftDown(SMALL_RECT);
private:
	SHORT bufferWidth, bufferHeight;
	CHAR_INFO* buffer;
	HANDLE handle;
	SMALL_RECT rectWindow;
};
