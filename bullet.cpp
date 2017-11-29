#include "bullet.h"

Bullet::Bullet(point start_pos, vector2d start_vel)
	: pos(start_pos), vel(start_vel)
{
	float magnitude = sqrt(vel.x*vel.x+vel.y*vel.y);

	if (magnitude != 0) {
		vel.x = vel.x/magnitude*BULLET_VEL_MAX_MAG;
		vel.y = vel.y/magnitude*BULLET_VEL_MAX_MAG;
	}
	else {
		vel.x = -1;
		vel.y = -1;
	}
}

Bullet::~Bullet() {
	destroy();
}

void Bullet::destroy() {
	draw(ILI9341_BLACK);
}

point Bullet::getPosition() {
	return pos;
}

void Bullet::updateAcceleration() {}

void Bullet::updateVelocity(float dt){
	vel.x += acc.x*dt;
	vel.y += acc.y*dt;
}

void Bullet::updateDisplacement(float dt) {
	pos.x += vel.x*dt;
	pos.y += vel.y*dt;

	if(!::on_screen(pos.x, pos.y)) {
		//Serial.println("Despawning bullet");
		despawn_bullet(this);
	}
}

void Bullet::update(float dt) {
	draw(ILI9341_BLACK);
	updateVelocity(dt);
	updateDisplacement(dt);
	draw(BULLET_COLOR);
}

void Bullet::draw(uint16_t color) {
	tft.drawPixel((uint16_t) pos.x, (uint16_t) pos.y, color);
}
