#pragma once
#define INTERVAL 17

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
enum class DIRECTION{ UP, DOWN, LEFT, RIGHT };
enum class TRAFFIC {RED = 79, YELLOW = 111, GREEN = 47};
enum class GAMESTATE {MENUING, RUNNING, PAUSED, EXITED};
enum class OPTIONS {CONTINUE, NEW_GAME, LOAD_GAME, SETTINGS, CREDIT, EXIT};


// (Dung xoa) unicode chars: ─ │
// https://www.piliapp.com/symbol/line