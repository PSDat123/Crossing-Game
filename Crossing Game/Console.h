#pragma once
#pragma execution_character_set( "utf-8" )
#include <iostream>
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

void SetConsoleSize(SHORT width, SHORT height);

void MoveConsole(int X, int Y);

void ChangeConsoleFontSize(SHORT);