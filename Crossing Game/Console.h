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

using namespace std;

void FixConsoleWindow();

void GotoXY(int, int);

void ChangeBackground();

void ClearBackground();

void ShowConsoleCursor(bool);

void GetConsoleSize(int& width, int& height);

void GetMaximumConsoleSize(int& width, int& height);

void SetConsoleSize(int& width, int& height);

void MoveConsole(int X, int Y);

void ChangeConsoleFontSize(SHORT);