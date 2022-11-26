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
		for (size_t i = 0; i < sprite.size(); ++i) {
			c->DrawString(empty, prev_x, prev_y + (int)i);
			if (x + length > max_x) {
				c->DrawString(sprite[i].substr(0, max_x - x), x, y + (int)i);
			}
			else {
				c->DrawString(sprite[i], x, y + (int)i);
			}
		}
	}
	else {
		size_t i = -x;
		for (size_t j = 0; j < sprite.size(); ++j) {
			if (i >= sprite[j].size()) continue;
			c->DrawString(sprite[j].substr(i), 0, y + (int)j);
		}
	}
}
