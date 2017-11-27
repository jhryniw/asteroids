#include "bullet.h"

Bullet::~Bullet() {
	destroy();
}

void Bullet::init(Adafruit_ILI9341* tft, float dx, float dy,
	float dir_x, float dir_y) {

	tft_ = tft;
	dx_ = dx;
	dy_ = dy;
	ax_ = 0;
	ay_ = 0;

	float vx = dir_x;
	float vy = dir_y;
	float magnitude = sqrt(vx*vx+vy*vy);
	if (magnitude != 0) {
		vx = vx/magnitude*BULLET_VEL_MAX_MAG;
		vy = vy/magnitude*BULLET_VEL_MAX_MAG;
	}
	else {
		vx = -1;
		vy = -1;
	}

	vx_ = vx;
	vy_ = vy;
}

void Bullet::destroy() {
	draw(ILI9341_BLACK);
}

point Bullet::getPosition() {
	return point(dx_, dy_);
}

void Bullet::updateAcceleration() {}

void Bullet::updateVelocity(){
	vx_ += ax_;
	vy_ += ay_;
}

void Bullet::updateDisplacement() {
	dx_ += vx_;
	dy_ += vy_;

	if(!::on_screen(dx_, dy_)) {
		Serial.println("Despawning bullet");
		despawn_bullet(this);
	}
}

void Bullet::update() {
	draw(ILI9341_BLACK);
	updateVelocity();
	updateDisplacement();
	draw(BULLET_COLOR);
}

void Bullet::draw(uint16_t color) {
	tft_->drawPixel((uint16_t) dx_, (uint16_t) dy_, color);
}
