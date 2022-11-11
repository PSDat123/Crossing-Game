#pragma once
#define UP_ARROW 72
#define DOWN_ARROW 80
#define ENTER_KEY 13

enum class DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum class GameState {
	MENUING,
	RUNNING,
	PAUSED,
	EXITED
};

enum class OPTIONS {
	CONTINUE,
	NEW_GAME,
	LOAD_GAME,
	SETTINGS,
	CREDIT,
	EXIT
};