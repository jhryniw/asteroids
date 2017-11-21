#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include <Arduino.h>
#include <Adafruit_ILI9341.h>

#define TFT_WIDTH 320
#define TFT_HEIGHT 240

#define ASTEROID_RADIUS 5
#define ASTEROID_COLOR ILI9341_WHITE
#define ASTEROID_VEL_MAG_MIN 0.5
#define ASTEROID_VEL_MAG_MAX 1.5
#define MAX_ASTEROIDS 20

#define SPAWN_DIST 15
#define SPAWN_LEFT (SPAWN_DIST*-1)
#define SPAWN_RIGHT (TFT_WIDTH+SPAWN_DIST)
#define SPAWN_UP (LOOP_DIST*-1)
#define SPAWN_DOWN (TFT_HEIGHT+SPAWN_DIST)

#define LOOP_DIST (SPAWN_DIST*2)
#define LOOP_LEFT (LOOP_DIST*-1)
#define LOOP_RIGHT (TFT_WIDTH+LOOP_DIST)
#define LOOP_UP (LOOP_DIST*-1)
#define LOOP_DOWN (TFT_HEIGHT+LOOP_DIST)

class Asteroid {
public:
	void init(Adafruit_ILI9341* tft);
	void init(Adafruit_ILI9341* tft, float dx, float dy);
	void init(Adafruit_ILI9341* tft, float dx, float dy,
		float vx, float vy);
	void initRand(Adafruit_ILI9341* tft);

	void update();

private:
	float dx_, dy_; // displacement
	float vx_, vy_; // velocity
	float ax_, ay_; // acceleration

	Adafruit_ILI9341* tft_;

	void draw_(uint16_t color);
	void updateAcceleration_();
	void updateVelocity_();
	void updateDisplacement_();
};

#endif
