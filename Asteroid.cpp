#include "Asteroid.h"

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

	Serial.print(" vx_: ");
	Serial.print(vx_);
	Serial.print(" vy_: ");
	Serial.println(vy_);
}

void Asteroid::updateAcceleration_() {}

void Asteroid::updateVelocity_() {
	vx_ += ax_;
	vy_ += ay_;
}

void Asteroid::updateDisplacement_() {
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

void Asteroid::update() {
	draw_(ILI9341_BLACK);
	updateAcceleration_();
	updateVelocity_();
	updateDisplacement_();
	draw_(ASTEROID_COLOR);
}

void Asteroid::draw_(uint16_t color) {
	tft_->drawCircle((uint16_t) dx_, (uint16_t) dy_, ASTEROID_RADIUS, color);
}
