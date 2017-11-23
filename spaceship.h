#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

#include <Arduino.h>
#include <Adafruit_ILI9341.h>

#include "inputs.h"
#include "bullet.h"

#define TFT_WIDTH 320
#define TFT_HEIGHT 240

#define SPACESHIP_RADIUS 5
#define SPACESHIP_COLOR ILI9341_WHITE
#define SPACESHIP_VEL_MAG_MAX 2
#define SPACESHIP_ACC_MAG 0.1

class Spaceship {
public:
	void init(Adafruit_ILI9341* tft);
	void init(Adafruit_ILI9341* tft, float dx, float dy);
	void init(Adafruit_ILI9341* tft, float dx, float dy,
		float vx, float vy, float ax, float ay);

	void update(float* sx, float* sy);

private:
	float dx_, dy_; // displacement
	float vx_, vy_; // velocity
	float ax_, ay_; // acceleration
	float ux_, uy_; // unit vector of ship direction

	Bullet bullet_;

	Adafruit_ILI9341* tft_;

	void draw(uint16_t color);
	void updateBullets();
	void updateAcceleration();
	void updateVelocity();
	void updateDisplacement();

};

#endif
