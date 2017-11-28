#include "spaceship.h"

Spaceship::Spaceship()
 : pos(TFT_WIDTH/2, TFT_HEIGHT/2), u(0, 1)
{

}

Spaceship::~Spaceship()
{

}

void Spaceship::updateAcceleration() {
	float ux = getJoystickHoriz();
	float uy = getJoystickVert();

	float magnitude = sqrt(ux*ux+uy*uy);
	if (magnitude != 0) {
		ux = ux/magnitude;
		uy = uy/magnitude;
		u = vector2d(ux, uy);
	}

	if (getButtonPress(BUTTON_1, false)) {
		acc.x = u.x*SPACESHIP_ACC_MAG;
		acc.y = u.y*SPACESHIP_ACC_MAG;
	}
	else {
		acc.x = sign(vel.x) * -0.01;
		acc.y = sign(vel.y) * -0.01;
	}
}

void Spaceship::updateVelocity(float dt) {
  Serial.println(dt);
	vel.x = constrain(vel.x+acc.x*dt, -SPACESHIP_VEL_MAG_MAX, SPACESHIP_VEL_MAG_MAX);
	vel.y = constrain(vel.y+acc.y*dt, -SPACESHIP_VEL_MAG_MAX, SPACESHIP_VEL_MAG_MAX);
}

void Spaceship::updateDisplacement(float dt) {
	pos.x = constrain(pos.x+vel.x*dt, 0, TFT_WIDTH);
	pos.y = constrain(pos.y+vel.y*dt, 0, TFT_HEIGHT);

	if (pos.x == 0 || pos.x == TFT_WIDTH) {
		vel.x = 0;
		acc.x = 0;
	}
	if (pos.y == 0 || pos.y == TFT_HEIGHT) {
		vel.y = 0;
		acc.y = 0;
	}
}

void Spaceship::update(float dt) {
	draw(ILI9341_BLACK);
	updateAcceleration();
	updateVelocity(dt);
	updateDisplacement(dt);
	fire();
	draw(SPACESHIP_COLOR);
}

void Spaceship::draw(uint16_t color) {
	tft.drawCircle((uint16_t) pos.x, (uint16_t) pos.y, SPACESHIP_RADIUS, color);
	tft.drawLine((uint16_t) pos.x, (uint16_t) pos.y,
		(uint16_t) pos.x+u.x*SPACESHIP_RADIUS,
			(uint16_t) pos.y+u.y*SPACESHIP_RADIUS, color);
}

void Spaceship::fire() {
	if (getButtonPress(BUTTON_2, true)) {
		Bullet new_bullet(pos, u);
		::spawn_bullet(&new_bullet);
	}
}
