#include "Lane.h"

Lane::Lane(SHORT x, SHORT y, SHORT width, SHORT height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	defaultCD = (float)(20 + rand() % 20);
	CD = defaultCD - rand() % int(defaultCD - 7);
	timeStamp = chrono::system_clock::now();
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
void Lane::increaseSpeed(float inc) {
	this->speed += inc;
}
SHORT Lane::getX() {
	return this->x;
}
SHORT Lane::getY() {
	return this->y;
}
SHORT Lane::getHeight() {
	return this->height;
}
void Lane::move(DIRECTION dir) {
	switch (dir)
	{
	case DIRECTION::UP: {
		break;
	}

	case DIRECTION::DOWN: {
		this->y += 1;
		for (Vehicle& v : qVehicle) {
			v.setVY(v.getVY() + 1);
		}
		break;
	}
	default:
		break;
	}
}

Vehicle Lane::getRandomVehicle(int x, int y) {
	int r = rand() % 10;
	if (!r) {
		Bird t = Bird(x, y, this->x, this->x + width, this->speed, this->dir);
		t.setVY(t.getVY() + rand() % (this->height - t.getHeight() + 1));
		return t;
	}
	if (r < 3) {
		Truck t = Truck(x, y, this->x, this->x + width, this->speed, this->dir);
		t.setVY(t.getVY() + rand() % (this->height - t.getHeight() + 1));
		return t;
	}
	if (r < 6) {
		Bike b = Bike(x, y, this->x, this->x + width, this->speed, this->dir);
		b.setVY(b.getVY() + rand() % (this->height - b.getHeight() + 1));
		return b;
	}
	Car c = Car(x, y, this->x, this->x + width, this->speed, this->dir);
	c.setVY(c.getVY() + rand() % (this->height - c.getHeight() + 1));
	return c;
}

void Lane::updateVehicles(Console* console) {
	if (trafficState == TRAFFIC::RED) return;
	int start_x = -1;
	float mult = 1;
	if (trafficState == TRAFFIC::YELLOW) mult = 0.5;
	if (dir == DIRECTION::LEFT) start_x = x + width;
	if (!qVehicle.empty()) {
		for (Vehicle& car : qVehicle) {
			car.update(mult);
		}
		if (dir == DIRECTION::RIGHT && qVehicle.back().getVX() >= start_x + minDist) {
			if (!(rand() % 30)) {
				qVehicle.push_back(getRandomVehicle(start_x, y + 1));
			}
		}
		else if (dir == DIRECTION::LEFT && qVehicle.back().getVX() + qVehicle.back().getLength() <= start_x - minDist) {
			if (!(rand() % 30)) {
				qVehicle.push_back(getRandomVehicle(start_x, y + 1));
			}
		}
		if (!qVehicle.front().getState()) {
			qVehicle.front().clear(console);
			qVehicle.pop_front();
		}
	}
	else {
		qVehicle.push_back(getRandomVehicle(start_x, y + 1));
	}
}

void Lane::updateTraffic() {
	chrono::system_clock::time_point t2 = std::chrono::system_clock::now();
	chrono::duration<float> elapsed = t2 - timeStamp;
	CD -= elapsed.count();
	timeStamp = t2;
	if (CD < 6) {
		trafficState = TRAFFIC::RED;
	}
	else if (CD < 10) {
		trafficState = TRAFFIC::YELLOW;
	}
	else {
		trafficState = TRAFFIC::GREEN;
	}
	if (CD < 0) CD = defaultCD;
}

void Lane::drawVehicles(Console* console) {
	for (Vehicle& v : qVehicle) {
		v.draw(console);
	}
}

void Lane::drawLane(Console* console) {
	if (this->y > 1) console->DrawHorizontalLine(L'—', x, x + width - 1, y);
	if (this->y + height > 0) console->DrawHorizontalLine(L'—', x, x + width - 1, y + height + 1);
}

void Lane::drawTrafficLight(Console* console) {
	if (this->y > 0) {
		if (dir == DIRECTION::RIGHT) {
			console->DrawPixel(x + width - 1, y + 1, short(trafficState));
		}
		else {
			console->DrawPixel(x, y + 1, short(trafficState));
		}
	}
}

void Lane::drawAll(Console* console) {
	drawVehicles(console);
	drawLane(console);
	drawTrafficLight(console);
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