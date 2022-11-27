#pragma once
#define INTERVAL 16

enum KEY {
	ENTER_KEY = 13,
	UP_ARROW = 72,
	DOWN_ARROW = 80,
	W = 87,
	A = 65,
	S = 83,
	D = 68
};
enum class DIRECTION{ UP, DOWN, LEFT, RIGHT };
enum class GameState {MENUING, RUNNING, PAUSED, EXITED};
enum class OPTIONS {CONTINUE, NEW_GAME, LOAD_GAME, SETTINGS, CREDIT, EXIT};

// (Dung xoa) unicode chars: ─ │
// https://www.piliapp.com/symbol/line