#include "Lane.h"

Lane::Lane(SHORT x, SHORT y, SHORT width, SHORT height, DIRECTION dir) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->dir = dir;
}

Lane::Lane() : Lane(0, 0, 100, 5) {}

Vehicle getRandomVehicle(int x, int y, int max_x, DIRECTION dir=DIRECTION::RIGHT) {
	int r = rand() % 10;
	if (r == 0) {
		return Truck(x, y, max_x, dir);
	}
	return Car(x, y, max_x, dir);
}

void Lane::updateVehicles(Console* console) {
	if (!qVehicle.empty()) {
		for (Vehicle& car : qVehicle) {
			car.move(dir);
		}
		++frameSinceLastVehicle;
		if (frameSinceLastVehicle > qVehicle.back().getLength() + 7) {
			if (!(rand() % 30)) {
				qVehicle.push_back(getRandomVehicle(-1, y + 1, width));
				frameSinceLastVehicle = 0;
			}
		}
		if (!qVehicle.front().getState()) {
			qVehicle.pop_front();
		}
	}
	else {
		qVehicle.push_back(getRandomVehicle(-1, y + 1, width));
		frameSinceLastVehicle = 0;
	}
}

void Lane::drawVehicles(Console* console) {
	for (Vehicle& v : qVehicle) {
		v.draw(console);
	}
}

void Lane::drawLane(Console* console) {
	console->DrawHorizontalLine(L'—', y);
	console->DrawHorizontalLine(L'—', y + height + 1);
}