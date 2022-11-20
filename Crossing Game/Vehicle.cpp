#include "Vehicle.h"

Vehicle::Vehicle(int x, int y) {
	/*this->sprite = {
		"  _______",
		" /|_||_\\ \\__",
		"|)         (\\",
		"=`(o)---(o)-J"
	};*/
	//this->sprite = {
	//	" _______________  _____",
	//	"|               ||___|_\\",
	//	"|===============|| -    |",
	//	"|               ||     (|",
	//	"'==(o)====(o)=======(o)=J "
	//};
	this->x = x;
	this->y = y;
	this->prev_x = x;
	this->prev_y = y;
	this->speed = 1;
	GetConsoleSize(this->max_x, this->max_y);
	this->length = 0;
	for (wstring& s : sprite) {
		if (s.size() > this->length) {
			this->length = s.size();
		}
	} 
}

void Vehicle::draw() {
	//GotoXY(this->prev_x, this->prev_y);
	//cout << "       ";
	//GotoXY(this->prev_x, this->prev_y + 1);
	//cout << "       ";
	//GotoXY(this->prev_x, this->prev_y + 2);
	//cout << "       ";
	//GotoXY(this->prev_x, this->prev_y + 3);
	//cout << "       ";

	//GotoXY(this->x, this->y);
	//cout << "  _______";
	//GotoXY(this->x, this->y + 1);
	//cout << " /|_||_\\ \\__";
	//GotoXY(this->x, this->y + 2);
	//cout << "|)         (\\";
	//GotoXY(this->x, this->y + 3);
	//cout << "=`(o)---(o)-J";
}

void Vehicle::move(DIRECTION dir) {
	switch (dir){
	case DIRECTION::UP:
		break;
	case DIRECTION::DOWN:
		break;
	case DIRECTION::LEFT:
		this->prev_x = this->x;
		this->x -= this->speed;
		break;
	case DIRECTION::RIGHT:
		this->prev_x = this->x;
		this->x += this->speed;
		break;
	default:
		break;
	}
	if (this->x + this->length < 0 || this->x > this->max_x) 
		this->state = false;
}

int Vehicle::getVX() {
	return this->x;
}

int Vehicle::getVY() {
	return this->y;
}

bool Vehicle::getState() {
	return this->state;
}

int Vehicle::getLength() {
	return this->length;
}
vector<vector<wstring>> Car::spriteSheet = {
	{
		L"  _______",
		L" /|_||_\\ \\__",
		L"|)         (\\",
		L"=`(o)---(o)-J"
	},
	{
		L" _.-.___\\__",
		L"|)        _`-.",
		L"'-(o)----(o)--`"
	},
	{
		L" _______________  _____",
		L"|               ||___|_\\",
		L"|===============|| -    |",
		L"|               ||     (|",
		L"'==(o)====(o)=======(o)=J "
	},
	{
		L"                  /\\\\      _____   ",
		L"    ,------      /  \\\\____/__|__\\_ ",
		L" ,--'---:---`--,/   |)       |   (|",
		L"==(o)-----(o)==J    `(o)=======(o)J"
	},
	{
		L"  __~@",
		L"  _`\\<,_",
		L"(*)/ (*)"
	}
};


Car::Car(int x, int y, int max_x, int max_y) {
	this->sprite = spriteSheet[rand() % spriteSheet.size()];
	this->speed = 1;
	this->empty = L"";
	this->length = 0;
	for (wstring& s : sprite) {
		if (s.size() > this->length) {
			this->length = s.size();
		}
	}
	this->empty.append(this->speed, L' ');

	if (x > -1) {
		this->x = x;
		this->y = y;
		this->prev_x = x;
		this->prev_y = y;
	}
	else {
		this->x = -this->length;
		this->y = y;
		this->prev_x = -this->length;
		this->prev_y = y;
	}
	this->max_x = max_x;
	this->max_y = max_y;
	if (this->x + this->length < 0 || this->x > this->max_x) this->state = false;
}

void Car::draw() {
	if (x >= 0) {
		//for (int i = 0; i < sprite.size(); ++i) {
		//	
		//	int j = 0;
		//	while (this->prev_x + j < this->max_x && j++ < this->speed) wcout << L' ';
		//}
		for (int i = 0; i < sprite.size(); ++i) {
			GotoXY(this->prev_x, this->prev_y + i);
			wcout << this->empty;
			GotoXY(this->x, this->y + i);
			if (this->x + this->length > this->max_x) {
				wcout << sprite[i].substr(0, this->max_x - this->x);
			}
			else {
				wcout << sprite[i];
			}
		}
	}
	else {
		int i = -this->x;
		for (int j = 0; j < sprite.size(); ++j) {
			if (i >= sprite[j].size()) continue;
			GotoXY(0, this->y + j);
			wcout << sprite[j].substr(i);
		}
	}
}

Truck::Truck(int x, int y) : Vehicle(x,y) {}

Vehicle::~Vehicle(){}