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

// Colors pixel black
void Bullet::destroy() {
	draw(ILI9341_BLACK);
}

// Returns position of bullet
point Bullet::getPosition() {
	return pos;
}

// Updates acceleration - not used
void Bullet::updateAcceleration() {}

// Adds acceleration to velocity
void Bullet::updateVelocity(float dt){
	vel.x += acc.x*dt;
	vel.y += acc.y*dt;
}

// Adds velocity to displacement
// Despawns bullet if it goes out of screen
void Bullet::updateDisplacement(float dt) {
	pos.x += vel.x*dt;
	pos.y += vel.y*dt;

	if(!::on_screen(pos.x, pos.y)) {
		//Serial.println("Despawning bullet");
		despawn_bullet(this);
	}
}

// Update values of bullet every frame
void Bullet::update(float dt) {
	draw(ILI9341_BLACK);
	updateVelocity(dt);
	updateDisplacement(dt);
	draw(BULLET_COLOR);
}

// Draws bullet
void Bullet::draw(uint16_t color) {
	tft.drawPixel((uint16_t) pos.x, (uint16_t) pos.y, color);
}
