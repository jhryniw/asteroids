#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

#include <Arduino.h>
#include <Adafruit_ILI9341.h>

#include "common.h"
#include "inputs.h"
#include "bullet.h"

#define SPACESHIP_RADIUS 5
#define SPACESHIP_COLOR ILI9341_WHITE
#define SPACESHIP_VEL_MAG_MAX 1
#define SPACESHIP_ACC_MAG 0.1

class Spaceship {
public:
	void init(Adafruit_ILI9341* tft);
	void init(Adafruit_ILI9341* tft, float dx, float dy);
	void init(Adafruit_ILI9341* tft, float dx, float dy,
		float vx, float vy, float ax, float ay);

	void update();

private:
	float dx_, dy_; // displacement
	float vx_, vy_; // velocity
	float ax_, ay_; // acceleration
	float sx_, sy_; // direction of ship

	Adafruit_ILI9341* tft_;

	void draw(uint16_t color);
	void updateAcceleration();
	void updateVelocity();
	void updateDisplacement();
	void fire();

};

#endif
