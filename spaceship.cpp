#include "spaceship.h"

void Spaceship::init(Adafruit_ILI9341* tft) {
	tft_ = tft;
	dx_ = 200;
	dy_ = 200;
	vx_ = 0;
	vy_ = 0;
	ax_ = 0;
	ay_ = 0;
	ux_ = 0;
	uy_ = -1;
}

void Spaceship::updateAcceleration() {
	float ux = getJoystickHoriz();
	float uy = getJoystickVert();

	float magnitude = sqrt(ux*ux+uy*uy);
	if (magnitude != 0) {
		ux = ux/magnitude;
		uy = uy/magnitude;
		ux_ = ux;
		uy_ = uy;
	}

	if (getButtonPress(BUTTON_1, false)) {
		ax_ = ux_*SPACESHIP_ACC_MAG;
		ay_ = uy_*SPACESHIP_ACC_MAG;
	}
	else {
		ax_ = 0;
		ay_ = 0;
	}
}

void Spaceship::updateVelocity() {
	vx_ = constrain(vx_+ax_, -SPACESHIP_VEL_MAG_MAX, SPACESHIP_VEL_MAG_MAX);
	vy_ = constrain(vy_+ay_, -SPACESHIP_VEL_MAG_MAX, SPACESHIP_VEL_MAG_MAX);
}

void Spaceship::updateDisplacement() {
	dx_ = constrain(dx_+vx_, 0, TFT_WIDTH);
	dy_ = constrain(dy_+vy_, 0, TFT_HEIGHT);

	if (dx_ == 0 || dx_ == TFT_WIDTH) {
		vx_ = 0;
		ax_ = 0;
	}
	if (dy_ == 0 || dy_ == TFT_HEIGHT) {
		vy_ = 0;
		ay_ = 0;
	}
}

void Spaceship::update(float &sx, float &sy) {
	draw(ILI9341_BLACK);
	updateAcceleration();
	updateVelocity();
	updateDisplacement();
	fire();
	draw(SPACESHIP_COLOR);
	sx = dx_;
	sy = dy_;
}

void Spaceship::draw(uint16_t color) {
	tft_->drawCircle((uint16_t) dx_, (uint16_t) dy_, SPACESHIP_RADIUS, color);
	tft_->drawLine((uint16_t) dx_, (uint16_t) dy_,
		(uint16_t) dx_+ux_*SPACESHIP_RADIUS,
			(uint16_t) dy_+uy_*SPACESHIP_RADIUS, color);
}

void Spaceship::fire() {
	if (getButtonPress(BUTTON_2, true)) {
		Bullet new_bullet;
		new_bullet.init(tft_, dx_, dy_, ux_, uy_);
		::spawn_bullet(&new_bullet);
	}
}
