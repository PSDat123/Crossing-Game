#pragma once
#pragma comment (lib, "winmm.lib") // Used to play sound
#pragma execution_character_set( "utf-8" )
#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <deque>

using namespace std;

void FixConsoleWindow();

void GotoXY(int, int);

void SetColor(int);

void ClearBackground();

void ShowConsoleCursor(bool);

void GetConsoleSize(SHORT& width, SHORT& height);

void GetMaximumConsoleSize(SHORT& width, SHORT& height);

void SetConsoleSize(SHORT& width, SHORT& height);

void MoveConsole(int X, int Y);

void ChangeConsoleFontSize(SHORT);