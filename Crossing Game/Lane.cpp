#include "Lane.h"

Lane::Lane(SHORT x, SHORT y, SHORT width, SHORT height, SHORT minDist, DIRECTION dir) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->dir = dir;
	this->minDist = minDist;
}

Lane::Lane() : Lane(0, 0, 100, 10, 5) {}

Vehicle getRandomVehicle(int x, int y, int min_x, int max_x, int max_y, DIRECTION dir = DIRECTION::RIGHT) {
	int r = rand() % 10;
	if (r < 2) {
		Truck t = Truck(x, y, max_x, min_x, dir);
		t.setVY(t.getVY() + rand() % (max_y - t.getHeight() + 1));
		return t;
	}
	if (r < 4) {
		Bike b = Bike(x, y, max_x, min_x, dir);
		b.setVY(b.getVY() + rand() % (max_y - b.getHeight() + 1));
		return b;
	}
	Car c = Car(x, y, max_x, min_x, dir);
	c.setVY(c.getVY() + rand() % (max_y - c.getHeight() + 1));
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
				qVehicle.push_back(getRandomVehicle(start_x, y + 1, x, x + width, height, dir));
			}
		}
		else if (dir == DIRECTION::LEFT && qVehicle.back().getVX() + qVehicle.back().getLength() < start_x - minDist) {
			if (!(rand() % 30)) {
				qVehicle.push_back(getRandomVehicle(start_x, y + 1, x, x + width, height, dir));
			}
		}
		if (!qVehicle.front().getState()) {
			qVehicle.pop_front();
		}
	}
	else {
		qVehicle.push_back(getRandomVehicle(start_x, y + 1, x, x + width, height, dir));
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