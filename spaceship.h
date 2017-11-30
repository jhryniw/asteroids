#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

#include <Arduino.h>
#include <Adafruit_ILI9341.h>

#include "common.h"
#include "inputs.h"
#include "bullet.h"

#define SPACESHIP_RADIUS 3
#define SPACESHIP_VEL_MAG_MAX 200
#define SPACESHIP_ACC_MAG 100
#define SPACESHIP_TRIANGLE_MAX 20
#define SPACESHIP_TRIANGLE_OFFSET 7
#define SPACESHIP_MAX_INVUL 2

extern Adafruit_ILI9341 tft;

class Spaceship {
public:
	Spaceship();
	~Spaceship();

	void reset();
	void update(float dt);
	point getVertexPos(int index);
	bool isInvul();

private:
	point pos;    // position
	vector2d vel; // velocity
	vector2d acc; // acceleration
	vector2d u;   // unit vector of ship direction
	bool invul;
	float invulTime;
	uint16_t spaceship_color;

	point vertices[3];
	point verticesOrig[3];

	Adafruit_ILI9341* tft_;

	void draw(uint16_t color);
	void updateAcceleration();
	void updateVelocity(float dt);
	void updateDisplacement(float dt);
	void updateInvul(float dt);
	void becomeInvul(float time);
	void fire();

	void updateVertices();
};

#endif
