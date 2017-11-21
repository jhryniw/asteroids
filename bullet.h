#ifndef __BULLET_H__
#define __BULLET_H__

#include <Arduino.h>
#include <Adafruit_ILI9341.h>

#define BULLET_COLOR ILI9341_WHITE
#define BULLET_VEL_MAX_MAG 4

class Bullet {
public:
	~Bullet();
	void init(Adafruit_ILI9341* tft, float dx, float dy,
		float dir_x, float dir_y);
	void update();
	void destroy();
private:
	float dx_, dy_; // displacement
	float vx_, vy_; // velocity
	float ax_, ay_; // acceleration

	Adafruit_ILI9341* tft_;

	void draw(uint16_t color);
	void updateAcceleration();
	void updateVelocity();
	void updateDisplacement();
};

#endif
