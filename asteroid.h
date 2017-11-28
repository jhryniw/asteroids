#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include <Adafruit_ILI9341.h>
#include "common.h"

#define ASTEROID_COLOR ILI9341_WHITE
#define ASTEROID_VEL_MAG_MIN 0.5
#define ASTEROID_VEL_MAG_MAX 1

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

extern Adafruit_ILI9341 tft;

class Asteroid : public polygon {
public:
	Asteroid();
	~Asteroid();

	void update();
	void destroy();
	bool isHit(point b);

	int index;

private:
	vector2 vel;  // velocity
	vector2 acc;  // acceleration

	void initRand();
	void generate_polygon(int size);

	void draw(uint16_t color);
	void updateAcceleration();
	void updateVelocity();
	void updateDisplacement();
};

#endif
