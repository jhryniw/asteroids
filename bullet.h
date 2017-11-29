#ifndef __BULLET_H__
#define __BULLET_H__

#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include "common.h"

#define BULLET_COLOR ILI9341_YELLOW
#define BULLET_VEL_MAX_MAG 50

extern Adafruit_ILI9341 tft;

class Bullet {
public:
	Bullet(point start_pos, vector2d start_vel);
	~Bullet();

	void update(float dt);
	void destroy();

	int index;
	point getPosition();

private:
	point pos;    // position
	vector2d vel; // velocity
	vector2d acc; // acceleration

	void draw(uint16_t color);
	void updateAcceleration();
	void updateVelocity(float dt);
	void updateDisplacement(float dt);
};

#endif
