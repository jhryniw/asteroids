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

	point pt[4];

	pt[0].px = -BOX_LEN; pt[0].py = -BOX_LEN;
	pt[1].px = BOX_LEN; pt[1].py = -BOX_LEN;
	pt[2].px = BOX_LEN; pt[2].py = BOX_LEN;
	pt[3].px = -BOX_LEN; pt[3].py = BOX_LEN;

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

void Asteroid::update(int sx, int sy) {
	draw(ILI9341_BLACK);
	updateAcceleration();
	updateVelocity();
	updateDisplacement();
	draw(ASTEROID_COLOR);
	isHit(sx, sy);
}

void Asteroid::draw(uint16_t color) {
	for (int i = 0; i < NUM_EDGES; i++) {
		tft_->drawLine(edge_[i].p1.px+dx_, edge_[i].p1.py+dy_,
			edge_[i].p2.px+dx_, edge_[i].p2.py+dy_, color);
	}

	//tft_->drawCircle((uint16_t) dx_, (uint16_t) dy_, ASTEROID_RADIUS, color);
}

bool Asteroid::rayTraceEdge(edge e, int bx, int by) {
	// Based on https://rosettacode.org/wiki/Ray-casting_algorithm
	int max_x = max(e.p1.px, e.p2.px)+dx_;
	//int min_x = min(e.p1.px, e.p2.px);
	int max_y = max(e.p1.py, e.p2.py)+dy_;
	int min_y = min(e.p1.py, e.p2.py)+dy_;

	return bx > max_x && by < max_y && by > min_y;
}

bool Asteroid::isHit(int bx, int by) {
	int counter = 0;

	for (int i = 0; i < NUM_EDGES; i++) {
		if (rayTraceEdge(edge_[i], bx, by)) {
			counter++;
		}
	}

	while(counter % 2 == 1) {}

	return counter % 2 == 1;
}
