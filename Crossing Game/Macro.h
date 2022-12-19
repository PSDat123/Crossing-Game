#pragma once
#pragma comment (lib, "winmm.lib")
#pragma execution_character_set( "utf-8" )
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <tchar.h>
#include <fstream>
#include <fcntl.h>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <ctime>
#include <deque>
#include <io.h>
#include <map>
#define INTERVAL 30
#define MAX_NAME_LENGTH 15
enum KEY {
	ENTER_KEY = 13,
	UP_ARROW = 72,
	DOWN_ARROW = 80,
	LEFT_ARROW = 75,
	RIGHT_ARROW = 77,
	ESC = 27,
	W = 87,
	A = 65,
	S = 83,
	D = 68
};
enum class DIRECTION{UP, DOWN, LEFT, RIGHT};
enum class TRAFFIC {RED = 79, YELLOW = 111, GREEN = 47};
enum class GAMESTATE {MENUING, RUNNING, PAUSED, EXITED, LOADING, SETTING};
enum class OPTIONS {CONTINUE, NEW_GAME, SAVE_GAME, LOAD_GAME, SETTINGS,
 										CREDIT, EXIT, RESUME, RESTART, RETURN};