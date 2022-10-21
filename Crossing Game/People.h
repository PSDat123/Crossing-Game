#pragma once

class People {
public:
	People();
	void Up();
	void Left();
	void Right();
	void Down();
	//bool isImpact();
	bool isFinish();
	bool isDead();
private:
	int x, y;
	bool state; // dead/alive
};