#include "Lane.h"

Lane::Lane(SHORT x, SHORT y, SHORT width, SHORT height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Lane::Lane() : Lane(0, 0, 100, 5) {}

void Lane::setDirection(DIRECTION dir) {
	this->dir = dir;
}
void Lane::setMinDist(SHORT minDist) {
	this->minDist = minDist;
}
void Lane::setSpeed(float speed) {
	this->speed = speed;
}

Vehicle Lane::getRandomVehicle(int x, int y) {
	int r = rand() % 10;
	if (r < 2) {
		Truck t = Truck(x, y, this->x, this->x + width, this->speed, this->dir);
		t.setVY(t.getVY() + rand() % (this->height - t.getHeight() + 1));
		return t;
	}
	if (r < 4) {
		Bike b = Bike(x, y, this->x, this->x + width, this->speed, this->dir);
		b.setVY(b.getVY() + rand() % (this->height - b.getHeight() + 1));
		return b;
	}
	Car c = Car(x, y, this->x, this->x + width, this->speed, this->dir);
	c.setVY(c.getVY() + rand() % (this->height - c.getHeight() + 1));
	return c;
}

void Lane::updateVehicles() {
	int start_x = -1;
	if (dir == DIRECTION::LEFT) start_x = x + width;
	if (!qVehicle.empty()) {
		for (Vehicle& car : qVehicle) {
			car.update();
		}
		if (dir == DIRECTION::RIGHT && qVehicle.back().getVX() > start_x + minDist) {
			if (!(rand() % 30)) {
				qVehicle.push_back(getRandomVehicle(start_x, y + 1));
			}
		}
		else if (dir == DIRECTION::LEFT && qVehicle.back().getVX() + qVehicle.back().getLength() < start_x - minDist) {
			if (!(rand() % 30)) {
				qVehicle.push_back(getRandomVehicle(start_x, y + 1));
			}
		}
		if (!qVehicle.front().getState()) {
			qVehicle.pop_front();
		}
	}
	else {
		qVehicle.push_back(getRandomVehicle(start_x, y + 1));
		frameSinceLastVehicle = 0;
	}

}

void Lane::drawVehicles(Console* console) {
	for (Vehicle& v : qVehicle) {
		v.draw(console);
	}
}

void Lane::drawLane(Console* console) {
	console->DrawHorizontalLine(L'—', x, x + width - 1, y);
	console->DrawHorizontalLine(L'—', x, x + width - 1, y + height + 1);
}

bool Lane::isInLane(People* p) {
	int pos = p->getY() + p->getHeight() - 1;
	if (pos > this->y && pos <= this->y + this->height) return true;
	return false;
}

bool Lane::checkCollison(People* p) {
	for (Vehicle& v : qVehicle) {
		if (v.checkCollision(p)) return true;
	}
	return false;
}