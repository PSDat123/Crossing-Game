#include "Vehicle.h"

Vehicle::Vehicle() : Vehicle(0, 0, 0, 0, {}) {}

Vehicle::Vehicle(float x, float y, SHORT min_x, SHORT max_x, vector<wstring> sprite, DIRECTION dir) {
	this->sprite = sprite;
	speed = 1;
	length = 0;
	for (wstring& s : sprite) {
		if ((int)s.size() > length) {
			length = (int)s.size();
		}
	}

	if (x > -1) {
		this->x = x;
		this->y = y;
		prev_x = x;
	}
	else {
		this->x = min_x - length;
		this->y = y;
		prev_x = min_x - length;
	}
	this->max_x = max_x;
	this->min_x = min_x;
	this->dir = dir;
	if (this->x + length < this->min_x || this->x > this->max_x) state = false;
}

Vehicle::~Vehicle() {}

void Vehicle::update() {
	switch (dir){
	case DIRECTION::LEFT:
		prev_x = ceil(x);
		x -= speed;
		break;
	case DIRECTION::RIGHT:
		prev_x = floor(x);
		x += speed;
		break;
	default:
		break;
	}
	if (x + length < min_x || x  > max_x) state = false;
}

void Vehicle::setVX(SHORT x) {
	this->prev_x = this->x;
	this->x = x;
	if (this->x + this->length < this->min_x || this->x  > this->max_x)
		this->state = false;
}

void Vehicle::setVY(SHORT y) {
	this->y = y;
}

int Vehicle::getVX() {
	return this->x;
}

int Vehicle::getVY() {
	return this->y;
}

int Vehicle::getHeight() {
	return this->sprite.size();
}

bool Vehicle::getState() {
	return this->state;
}


int Vehicle::getLength() {
	return this->length;
}

void Vehicle::draw(Console* c) {
	if (dir == DIRECTION::RIGHT) {
		if (x > min_x) {
			for (size_t i = 0; i < sprite.size(); ++i) {
				c->DrawHorizontalLine(L' ', prev_x, x - 1, y + i);
				if (x + sprite[i].size() > max_x) {
					c->DrawString(sprite[i].substr(0, max_x - x), x, y + (int)i);
				}
				else {
					c->DrawString(sprite[i], x, y + (int)i);
				}
			}
			return;
		}
		size_t i = min_x - x;
		for (size_t j = 0; j < sprite.size(); ++j) {
			if (i >= sprite[j].size()) continue;
			c->DrawString(sprite[j].substr(i), min_x, y + (int)j);
		}
		return;
	}
	if(x + length < max_x){
		for (size_t i = 0; i < sprite.size(); ++i) {
			int l = sprite[i].size();
			c->DrawHorizontalLine(L' ', x + l, prev_x + l - 1, y + i);
			if (x < min_x) {
				c->DrawString(sprite[i].substr(min_x - x), min_x, y + (int)i);
			}
			else {
				c->DrawString(sprite[i], x, y + (int)i);
			}
		}
		return;
	}
	size_t i = max_x - x;
	for (size_t j = 0; j < sprite.size(); ++j) {
		if (i >= sprite[j].size()) continue;
		c->DrawString(sprite[j].substr(0, i), x, y + (int)j);
	}
	
}
