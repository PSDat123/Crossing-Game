#include "Vehicle.h"


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

void Vehicle::draw(Console* c) {
	if (x >= 0) {
		for (int i = 0; i < sprite.size(); ++i) {
			c->DrawString(empty, prev_x, prev_y + i);
			if (x + length > max_x) {
				c->DrawString(sprite[i].substr(0, max_x - x), x, y + i);
			}
			else {
				c->DrawString(sprite[i], x, y + i);
			}
		}
	}
	else {
		int i = -x;
		for (int j = 0; j < sprite.size(); ++j) {
			if (i >= sprite[j].size()) continue;
			c->DrawString(sprite[j].substr(i), 0, y + j);
		}
	}
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