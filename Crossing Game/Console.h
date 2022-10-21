#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>

using namespace std;

void FixConsoleWindow();

void GotoXY(int, int);

bool KeyHit(int);

void ChangeBackground();

void ClearBackground();