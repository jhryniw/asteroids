#ifndef __BULLET_H__
#define __BULLET_H__

#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include "common.h"

#define BULLET_COLOR ILI9341_YELLOW
#define BULLET_VEL_MAX_MAG 500

extern Adafruit_ILI9341 tft;

class Bullet {
public:
	Bullet(point start_pos, vector2d start_vel); // Ctor
	~Bullet(); // Dtor

	/*
		Updates values of bullet every frame
		@param dt delta time since last frame
	*/
	void update(float dt);

	/*
		Colors pixel black
	*/
	void destroy();

	int index;

	/*
		Returns position of bullet
		@return position
	*/
	point getPosition();

private:
	point pos;    // position
	vector2d vel; // velocity
	vector2d acc; // acceleration

	/*
		Draws bullet
		@param color color to draw
	*/
	void draw(uint16_t color);

	/*
		Updates acceleration
		Not used
	*/
	void updateAcceleration();

	/*
		Adds acceleration to velocity
		@param dt delta time since last frame
	*/
	void updateVelocity(float dt);

	/*
		Adds velocity to displacement
		Despawns bullet if it goes off screen
		@param dt delta time since last frame
	*/
	void updateDisplacement(float dt);
};

#endif
