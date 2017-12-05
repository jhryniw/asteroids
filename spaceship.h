#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

#include <Arduino.h>
#include <Adafruit_ILI9341.h>

#include "common.h"
#include "inputs.h"
#include "bullet.h"

#define SPACESHIP_RADIUS 3
#define SPACESHIP_VEL_MAG_MAX 200
#define SPACESHIP_ACC_MAG 200
#define SPACESHIP_TRIANGLE_MAX 20
#define SPACESHIP_TRIANGLE_OFFSET 7
#define SPACESHIP_MAX_INVUL 2

extern Adafruit_ILI9341 tft;

class Spaceship {
public:
	Spaceship(); // Ctor
	~Spaceship(); // Dtor

	/*
		Sets values to values at respawn
	*/
	void reset();

	/*
		Updates values and states of ship every frame
		@param dt delta time since last frame (seconds)
	*/
	void update(float dt);

	/*
		Returns coordinates of a ship vertex at index
		@param index index value of vertices[]
		@return coordinates of point
	*/
	point getVertexPos(int index);

	/*
		Returns if ship is invulnerable
		@return invulnerability flag
	*/
	bool isInvul();

private:
	point pos;    // position
	vector2d vel; // velocity
	vector2d acc; // acceleration
	vector2d u;   // unit vector of ship direction
	bool invul;
	float invulTime;
	uint16_t spaceship_color;

	point vertices[3];	// Vertices offset at ship pos
	point verticesOrig[3]; // Vertices offset at (0,0)

	Adafruit_ILI9341* tft_;

	/*
		Draws triangle using ship vertices
		@param color color of ship
	*/
	void draw(uint16_t color);

	/*
		Updates direction and acceleration of ship
	*/
	void updateAcceleration();

	/*
		Updates velocity of ship
		@param dt delta time since last frame (seconds)
	*/
	void updateVelocity(float dt);

	/*
		Updates displacement of ship
		@param dt delta time since last frame (seconds)
	*/
	void updateDisplacement(float dt);

	/*
		Counts down invulnerability timer
		@param dt delta time since last frame (seconds)
	*/
	void updateInvul(float dt);

	/*
		Sets ship as invincible
		@param time length of invulnerability
	*/
	void becomeInvul(float time);

	/*
		Shoots bullet if button 1 is pressed
	*/
	void fire();

	/*
		Updates positions of ship vertices
	*/
	void updateVertices();
};

#endif
