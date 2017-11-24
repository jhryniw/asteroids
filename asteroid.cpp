#include "asteroid.h"

void Asteroid::init(Adafruit_ILI9341* tft) {
	tft_ = tft;
	dx_ = 100;
	dy_ = 100;
	vx_ = -0.5;
	vy_ = -0.5;
	ax_ = 0;
	ay_ = 0;
}

void Asteroid::init(Adafruit_ILI9341* tft, float dx, float dy) {
	tft_ = tft;
	dx_ = dx;
	dy_ = dy;
	vx_ = -0.5;
	vy_ = -0.5;
	ax_ = 0;
	ay_ = 0;
}

void Asteroid::init(Adafruit_ILI9341* tft, float dx, float dy,
	float vx, float vy) {

	tft_ = tft;
	dx_ = dx;
	dy_ = dy;
	vx_ = vx;
	vy_ = vy;
	ax_ = 0;
	ay_ = 0;
}

void Asteroid::initRand(Adafruit_ILI9341* tft) {
	tft_ = tft;
	float sign;

	switch (random(4)) {
		case 0:
			dx_ = SPAWN_LEFT;
			dy_ = random(SPAWN_UP, SPAWN_DOWN+1);
			break;
		case 1:
			dx_ = SPAWN_RIGHT;
			dy_ = random(SPAWN_UP, SPAWN_DOWN+1);
			break;
		case 2:
			dx_ = random(SPAWN_LEFT, SPAWN_RIGHT+1);
			dy_ = SPAWN_UP;
			break;
		case 3:
			dx_ = random(SPAWN_LEFT, SPAWN_RIGHT+1);
			dy_ = SPAWN_DOWN;
			break;
	}

	sign = random(2)*2-1;
	vx_ = random(ASTEROID_VEL_MAG_MIN*100, ASTEROID_VEL_MAG_MAX*100+1);
	vx_ = vx_/100*sign;

	sign = random(2)*2-1;
	vy_ = random(ASTEROID_VEL_MAG_MIN*100, ASTEROID_VEL_MAG_MAX*100+1);
	vy_ = vy_/100*sign;

	ax_ = 0;
	ay_ = 0;

	point pt[] = {
		{0, 20},
		{20, 0},
		{0, -20},
		{-20, 0}
	};

	edge_[0].p1 = pt[0];
	edge_[0].p2 = pt[1];

	edge_[1].p1 = pt[1];
	edge_[1].p2 = pt[2];

	edge_[2].p1 = pt[2];
	edge_[2].p2 = pt[3];

	edge_[3].p1 = pt[0];
	edge_[3].p2 = pt[3];
}

void Asteroid::updateAcceleration() {}

void Asteroid::updateVelocity() {
	vx_ += ax_;
	vy_ += ay_;
}

void Asteroid::updateDisplacement() {
	dx_ = constrain(dx_+vx_, LOOP_LEFT, LOOP_RIGHT);
	dy_ = constrain(dy_+vy_, LOOP_UP, LOOP_DOWN);

	if (dx_ == LOOP_LEFT) {
		dx_ = LOOP_RIGHT;
	}
	else if (dx_ == LOOP_RIGHT) {
		dx_ = LOOP_LEFT;
	}
	if (dy_ == LOOP_UP) {
		dy_ = LOOP_DOWN;
	}
	else if (dy_ == LOOP_DOWN) {
		dy_ = LOOP_UP;
	}
}

void Asteroid::update(float sx, float sy) {
	draw(ILI9341_BLACK);
	updateAcceleration();
	updateVelocity();
	updateDisplacement();
	draw(ASTEROID_COLOR);
	isHit(sx, sy);
}

void Asteroid::draw(uint16_t color) {
	for (int i = 0; i < 4; i++) {
		tft_->drawLine(edge_[i].p1.x+dx_, edge_[i].p1.y+dy_,
			edge_[i].p2.x+dx_, edge_[i].p2.y+dy_, color);
	}
}

bool Asteroid::rayTraceEdge(edge e, float x, float y) {
	/*
		Ray casting based on
		https://rosettacode.org/wiki/Ray-casting_algorithm

		Line intersection based on
		https://www.topcoder.com/community/data-science/data-science-tutorials/
		geometry-concepts-line-intersection-and-its-applications/
	*/

	float tx = x - dx_;
	float ty = y - dy_;

	if (e.p1.y == e.p2.y || tx < min(e.p1.x, e.p2.x) ||
		ty > max(e.p1.y, e.p2.y) || ty < min(e.p1.y, e.p2.y)) {
			return false;
	}

	if (tx > max(e.p1.x, e.p2.x)) {
		return true;
	}

	float a1 = e.p2.y - e.p1.y;
	float b1 = e.p1.x - e.p2.x;
	float c1 = a1 * e.p1.x + b1 * e.p1.y;

	// float a1 = 0;
	float b2 = -tx;
	float c2 = b2 * ty;

	float det = a1 * b2;

	// since parallel lines return false, det != 0
	float x_min = (b2 * c1 - b1 * c2) / det;

	/*
	Serial.println("-");
	Serial.print("x1: ");
	Serial.print(e.p1.x);
	Serial.print(" y1: ");
	Serial.print(e.p1.y);
	Serial.print(" x2: ");
	Serial.print(e.p2.x);
	Serial.print(" y2: ");
	Serial.println(e.p2.y);
	Serial.print("a1: ");
	Serial.print(a1);
	Serial.print(" b1: ");
	Serial.print(b1);
	Serial.print(" c1: ");
	Serial.print(c1);
	Serial.print(" a2: ");
	Serial.print(a2);
	Serial.print(" b2: ");
	Serial.print(b2);
	Serial.print(" c2: ");
	Serial.print(c2);
	Serial.print(" det: ");
	Serial.println(det);
	Serial.print("tx: ");
	Serial.print(tx);
	Serial.print(" ty: ");
	Serial.print(ty);
	Serial.print(" max x: ");
	Serial.println(x_threshold);
	Serial.println("-");
	*/
	return tx >= x_min;
}

bool Asteroid::isHit(float bx, float by) {
	int counter = 0;

	for (int i = 0; i < 4; i++) {
		if (rayTraceEdge(edge_[i], bx, by)) {
			counter++;
		}
	}

	if (counter % 2 == 1) {
		Serial.println("hit");
		while (true) {}
	}

	return counter % 2 == 1;
}
