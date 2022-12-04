#pragma once
#pragma comment (lib, "winmm.lib") // Used to play sound
#pragma execution_character_set( "utf-8" )
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <string>
#include <tchar.h>
#include <vector>
#include <chrono>
#include <thread>
#include <deque>
#include <map>

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

	void DrawString(wstring s, int x, int y, short col = 240);

	void DrawHorizontalLine(wchar_t c, int start_x, int end_x, int y, short col = 240);

	void DrawVerticalLine(wchar_t c, int x, short col = 240);

	void ShiftUp(SMALL_RECT rect);

	void ShiftDown(SMALL_RECT rect);

private:
	SHORT bufferWidth, bufferHeight;
	CHAR_INFO* buffer;
	HANDLE handle;
	SMALL_RECT rectWindow;
};
