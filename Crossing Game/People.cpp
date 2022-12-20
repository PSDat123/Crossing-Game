#include "People.h"

vector<wstring> People::sprite = {
	L" o ",
	L"/X\\",
	L" A "
};

People::People(int cur_x, int cur_y, SMALL_RECT bounds) {
	this->x = cur_x;
	this->y = cur_y;
	this->prev_x = x;
	this->prev_y = y;
	this->state = true;
	this->bounds = bounds;
	this->height = sprite.size();

	this->width = 0;
	for (wstring& s : sprite) {
		if ((int)s.size() > width) {
			width = (int)s.size();
		}
	}
	this->speed = sprite.size();
}

People::People() : People(0, 0, {0, 0, 0, 0}) {}

void People::setPos(int x, int y) {
	this->x = x;
	this->y = y;
	this->prev_x = x;
	this->prev_y = y;
}

void People::setBound(SMALL_RECT bounds) {
	this->bounds = bounds;
}

void People::setState(bool state) {
	this->state = state;
}

void People::setName(char name[MAX_NAME_LENGTH]) {
	strcpy_s(this->name, name);
}
void People::setLife(int life) {
	this->life = life;
}


void People::move(DIRECTION dir) {
	switch (dir){
	case DIRECTION::UP:
		prev_x = x;
		prev_y = y;
		y -= speed;
		if (y < bounds.Top) y = bounds.Top;
		break;
	case DIRECTION::DOWN:
		prev_x = x;
		prev_y = y;
		y += speed;
		if (y > bounds.Bottom - height) y = bounds.Bottom - height;
		break;
	case DIRECTION::LEFT:
		prev_x = x;
		prev_y = y;
		x -= speed;
		if (x < bounds.Left) x = bounds.Left;
		break;
	case DIRECTION::RIGHT:
		prev_x = x;
		prev_y = y;
		x += speed;
		if (x > bounds.Right - width) x = bounds.Right - width;
		break;
	default:
		break;
	}
}
void People::update() {
	prev_x = x;
	prev_y = y;
}

void People::draw(Console* c) {
	for (size_t i = 0; i < height; ++i) {
		c->DrawHorizontalLine(L' ', prev_x, prev_x + width - 1, prev_y + i);
	}
	for (size_t i = 0; i < height; ++i) {
		c->DrawString(sprite[i], x, y + i);
	}
}

void People::erase(Console* c) {
	for (size_t i = 0; i < height; ++i) {
		c->DrawHorizontalLine(L' ', x, x + width - 1, y + i);
	}
}

int People::getX() {
	return this->x;
}

int People::getY() {
	return this->y;
}

int People::getHeight() {
	return this->height;
}

int People::getWidth() {
	return this->width;
}

int People::getLife() {
	return this->life;
}

char* People::getName() {
	return this->name;
}

People::~People() {}

bool People::isDead() {
	return !state;
}

void People::removeLife(int n) {
	this->life -= n;
	if (life < 1) this->state = false;
}

void People::addLife(int n) {
	this->life += n;
}
