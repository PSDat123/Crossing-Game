#pragma once
#include "Console.h"
#include "Macro.h"

class People {
public:
	static vector<wstring> sprite;
	People();
	People(int x, int y, SMALL_RECT bounds);
	~People();

	int getX();
	int getY();
	int getHeight();
	int getWidth();
	int getLife();
	char* getName();

	void setPos(int x, int y);
	void setBound(SMALL_RECT);
	void setState(bool);
	void setLife(int);
	void setName(char name[MAX_NAME_LENGTH]);

	void move(DIRECTION);
	void update();
	void draw(Console*);
	void removeLife(int);
	void addLife(int);
	//bool isImpact(Vehicle*);
	//bool isImpact(Animal*);
	bool isFinish();
	bool isDead();
private:
	int x, y, prev_x, prev_y, speed;
	int height, width, life=3;
	char name[MAX_NAME_LENGTH] = "Dat2Phit";
	SMALL_RECT bounds;
	bool state; // dead/alive
	//bool checkFrame(int, int);
};