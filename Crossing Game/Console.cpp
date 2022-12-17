#include "Console.h"

Console::Console() {
	bufferWidth = 140;
	bufferHeight = 50;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	buffer = new CHAR_INFO[bufferWidth * bufferHeight];
	memset(buffer, 0, sizeof(CHAR_INFO) * bufferWidth * bufferHeight);
	MoveConsole(100, 0);
	ChangeConsoleFontSize(18);
	SetConsoleSize(bufferWidth, bufferHeight);
	SetConsoleTextAttribute(handle, 240);
	SetConsoleOutputCP(CP_UTF8);
	ChangeBackgroundColor(240);
	FixConsoleWindow();
	ShowConsoleCursor(false);
	ClearBackground();
	SetConsoleTitle(L"The Jaywalker");
}

Console::~Console() {
	delete[] buffer;
}

void Console::FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void Console::GetConsoleSize(SHORT& width, SHORT& height) {
	width = bufferWidth;
	height = bufferHeight;
}

void Console::GetMaximumConsoleSize(SHORT& width, SHORT& height) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	width = info.dwMaximumWindowSize.X;
	height = info.dwMaximumWindowSize.Y;
}

void Console::SetConsoleSize(SHORT& width, SHORT& height) {
	SMALL_RECT WindowSize = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(handle, TRUE, &WindowSize);
	SetConsoleScreenBufferSize(handle, {width, height});
	SetConsoleActiveScreenBuffer(handle);
	WindowSize.Right = width - 1;
	WindowSize.Bottom = height - 1;
	rectWindow = WindowSize;
	if (!SetConsoleWindowInfo(handle, TRUE, &WindowSize)) {
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(handle, &info);
		WindowSize.Right = info.dwMaximumWindowSize.X - 1;
		WindowSize.Bottom = info.dwMaximumWindowSize.Y - 1;
		rectWindow = WindowSize;
		SetConsoleWindowInfo(handle, TRUE, &WindowSize);
		width = info.dwMaximumWindowSize.X;
		height = info.dwMaximumWindowSize.Y;
		SetConsoleScreenBufferSize(handle, { width, height });
	}
}

void Console::GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}

void Console::ShowConsoleCursor(bool show){
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = show;
	SetConsoleCursorInfo(handle, &cursorInfo);
}

void Console::MoveConsole(int x, int y) {
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void Console::ChangeConsoleFontSize(SHORT h) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                  
	cfi.dwFontSize.Y = h;                  
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_BOLD;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(handle, FALSE, &cfi);
}

void Console::ChangeBackgroundColor(int colorCode) {
	int n = bufferWidth * bufferHeight;
	for (int i = 0; i < n; ++i) {
		buffer[i].Attributes = colorCode;
	}
}

void Console::ClearBackground() {
	int n = bufferWidth * bufferHeight;
	for (int i = 0; i < n; ++i) {
		buffer[i].Char.UnicodeChar = 0;
		buffer[i].Attributes = 240;
	}
}

void Console::UpdateScreen() {
	WriteConsoleOutput(handle, buffer, { bufferWidth, bufferHeight }, { 0,0 }, &rectWindow);
}

void Console::DrawChar(wchar_t c, int x, int y, short col) {
	buffer[y * bufferWidth + x].Char.UnicodeChar = c;
	buffer[y * bufferWidth + x].Attributes = col;
}

void Console::DrawPixel(int x, int y, short col) {
	buffer[y * bufferWidth + x].Attributes = col;
}

void Console::DrawString(wstring s, int x, int y, short col) {
	for (size_t i = 0; i < s.size(); ++i) {
		buffer[y * bufferWidth + x + i].Char.UnicodeChar = s[i];
		buffer[y * bufferWidth + x + i].Attributes = col;
	}
}

void Console::DrawHorizontalLine(wchar_t c, int start_x, int end_x, int y, short col) {
	for (SHORT i = start_x; i <= end_x; ++i) {
		buffer[y * bufferWidth + i].Char.UnicodeChar = c;
		buffer[y * bufferWidth + i].Attributes = col;
	}
}

void Console::DrawVerticalLine(wchar_t c, int x, int start_y, int end_y, short col) {
	for (SHORT i = start_y; i <= end_y; ++i) {
		buffer[i * bufferWidth + x].Char.UnicodeChar = c;
		buffer[i * bufferWidth + x].Attributes = col;
	}
}

void Console::ShiftUp(SMALL_RECT rect) {
	SHORT i = rect.Top;
	for (; i < rect.Bottom; ++i) {
		for (SHORT j = rect.Left; j <= rect.Right; ++j) {
			buffer[i * bufferWidth + j] = buffer[(i + 1) * bufferWidth + j];
		}
	}
	DrawHorizontalLine(L' ', rect.Left, rect.Right, i);
}

void Console::ShiftDown(SMALL_RECT rect) {
	SHORT i = rect.Bottom;
	for (; i > rect.Top; --i) {
		for (SHORT j = rect.Left; j <= rect.Right; ++j) {
			buffer[i * bufferWidth + j] = buffer[(i - 1) * bufferWidth + j];
		}
	}
	DrawHorizontalLine(L' ', rect.Left, rect.Right, i);
}