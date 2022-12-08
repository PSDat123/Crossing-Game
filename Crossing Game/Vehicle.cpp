#include "Vehicle.h"

Vehicle::Vehicle() : Vehicle(0, 0, 0, 0, 0, {}) {}

Vehicle::Vehicle(float x, float y, SHORT min_x, SHORT max_x, float speed, vector<wstring> sprite, DIRECTION dir) {
	this->sprite = sprite;
	this->speed = speed;
	length = 0;
	this->height = sprite.size();
	for (wstring& s : sprite) {
		if ((int)s.size() > length) {
			length = (int)s.size();
		}
	}

	if (x > -1) {
		this->x = x;
		this->y = y;
		prev_x = (int)x;
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

void Vehicle::update(float mult) {
	switch (dir){
	case DIRECTION::LEFT:
		prev_x = x;
		x -= speed * mult;
		break;
	case DIRECTION::RIGHT:
		prev_x = x;
		x += speed * mult;
		break;
	default:
		break;
	}
	if (floor(x) + length < min_x || int(x)  > max_x)
		state = false;
}

void Vehicle::setVX(SHORT x) {
	this->prev_x = this->x;
	this->x = x;
	if (floor(this->x) + this->length < this->min_x || int(this->x)  > this->max_x)
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
	return this->height;
}

bool Vehicle::getState() {
	return this->state;
}


int Vehicle::getLength() {
	return this->length;
}

void Vehicle::clear(Console* c) {
	if (dir == DIRECTION::RIGHT) {
		for (size_t i = 0; i < height; ++i) {
			if (this->state) c->DrawHorizontalLine(L' ', prev_x, x - 1, y + i);
			else c->DrawHorizontalLine(L' ', prev_x, max_x - 1, y + i);
		}
		return;
	}
	for (size_t i = 0; i < height; ++i) {
		int l = sprite[i].size();
		if (this->state) c->DrawHorizontalLine(L' ', x + l, prev_x + l - 1, y + i);
		else c->DrawHorizontalLine(L' ', min_x, prev_x + l - 1, y + i);
		
	}
}

void Vehicle::draw(Console* c) {
	if (dir == DIRECTION::RIGHT) {
		if (int(x) > min_x) {
			for (size_t i = 0; i < height; ++i) {
				if(prev_x < min_x) c->DrawHorizontalLine(L' ', min_x, x - 1, y + i);
				else c->DrawHorizontalLine(L' ', prev_x, x - 1, y + i);
				if (int(x) + sprite[i].size() > max_x) {
					c->DrawString(sprite[i].substr(0, max_x - floor(x)), x, y + (int)i);
				}
				else {
					c->DrawString(sprite[i], x, y + (int)i);
				}
			}
			return;
		}
		size_t i = min_x - floor(x);
		for (size_t j = 0; j < height; ++j) {
			if (i > sprite[j].size()) continue;
			c->DrawString(sprite[j].substr(i), min_x, y + (int)j);
		}
		return;
	}
	if(floor(x) + length < max_x){
		for (size_t i = 0; i < height; ++i) {
			int l = sprite[i].size();
			if(prev_x + l >= max_x) c->DrawHorizontalLine(L' ', x + l, max_x - 1, y + i);
			else c->DrawHorizontalLine(L' ', x + l, prev_x + l - 1, y + i);
			if (floor(x) < min_x) {
				c->DrawString(sprite[i].substr(min_x - floor(x)), min_x, y + (int)i);
			}
			else {
				c->DrawString(sprite[i], x, y + (int)i);
			}
		}
		return;
	}
	size_t i = max_x - int(x);
	for (size_t j = 0; j < height; ++j) {
		if (i > sprite[j].size()) continue;
		c->DrawString(sprite[j].substr(0, i), x, y + (int)j);
	}
	
}

bool Vehicle::checkCollision(People* p) {
	if (
		this->x < p->getX() + p->getWidth() &&
		this->x + this->length > p->getX() &&
		this->y < p->getY() + p->getHeight() &&
		this->height + this->y > p->getY()
		) {
		return true;
	}
	return false;
}