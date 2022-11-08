#include "Console.h"


void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GetConsoleSize(int& width, int& height) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	width = info.dwSize.X;
	height = info.dwSize.Y;
}

void GetMaximumConsoleSize(int& width, int& height) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	width = info.dwMaximumWindowSize.X;
	height = info.dwMaximumWindowSize.Y;
}

void SetConsoleSize(SHORT width, SHORT height) {
	SMALL_RECT WindowSize = { 0, 0, 1, 1 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD NewSize;

	NewSize.X = width;
	NewSize.Y = height;
	SetConsoleWindowInfo(console, TRUE, &WindowSize);
	int failed = 0;
	SetConsoleScreenBufferSize(console, NewSize);
	SetConsoleActiveScreenBuffer(console);
	WindowSize.Right = width - 1;
	WindowSize.Bottom = height - 1;
	if (!SetConsoleWindowInfo(console, TRUE, &WindowSize)) {
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(console, &info);
		WindowSize.Right = info.dwMaximumWindowSize.X - 1;
		WindowSize.Bottom = info.dwMaximumWindowSize.Y - 1;
		SetConsoleWindowInfo(console, TRUE, &WindowSize);
		NewSize.X = info.dwMaximumWindowSize.X;
		NewSize.Y = info.dwMaximumWindowSize.Y;
		SetConsoleScreenBufferSize(console, NewSize);
	}
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowConsoleCursor(bool show){
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = show;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void MoveConsole(int x, int y) {
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void ChangeConsoleFontSize(SHORT h) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                  
	cfi.dwFontSize.Y = h;                  
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_BOLD;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void ChangeBackground() {
	system("color f0");
}

void ClearBackground() {
	system("cls");
}