#include "Vehicle.h"

Vehicle::~Vehicle() {}

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
	if (this->x + this->length < this->min_x || this->x  > this->max_x) 
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
	if (dir == DIRECTION::RIGHT) {
		if (x > min_x) {
			for (size_t i = 0; i < sprite.size(); ++i) {
				for (int j = prev_x; j < x; ++j)
					c->DrawChar(L' ', j, prev_y + i);
				//c->DrawString(empty, prev_x, prev_y + i);
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
			for (int j = x + l; j < prev_x + l; ++j)
				c->DrawChar(L' ', j, prev_y + i);
			//c->DrawString(empty, prev_x, prev_y + i);
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
