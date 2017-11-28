#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

#include <Arduino.h>
#include <Adafruit_ILI9341.h>

#include "common.h"
#include "inputs.h"
#include "bullet.h"

#define SPACESHIP_RADIUS 5
#define SPACESHIP_COLOR ILI9341_CYAN
#define SPACESHIP_VEL_MAG_MAX (1.5/5)
#define SPACESHIP_ACC_MAG 0.1

extern Adafruit_ILI9341 tft;

class Spaceship {
public:
	Spaceship();
	~Spaceship();

	void update(float dt);

private:
	point pos;    // position
	vector2d vel; // velocity
	vector2d acc; // acceleration
	vector2d u;   // unit vector of ship direction

	Adafruit_ILI9341* tft_;

	void draw(uint16_t color);
	void updateAcceleration();
	void updateVelocity(float dt);
	void updateDisplacement(float dt);
	void fire();

};

#endif
