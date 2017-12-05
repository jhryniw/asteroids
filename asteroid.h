#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include <Adafruit_ILI9341.h>
#include "common.h"

#define ASTEROID_COLOR ILI9341_WHITE
#define ASTEROID_VEL_MAG_MIN 30
#define ASTEROID_VEL_MAG_MAX 100

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

/**
 * Represents an asteroid in the game
 */
class Asteroid : public polygon {
public:
	/**
	 * Construct a random asteroid
	 */
	Asteroid();

	/**
	 * Construct an asteroid with starting physical parameters
	 */
	Asteroid(point pos, vector2d vel, vector2d acc, int size);

	// Dtor
	~Asteroid();

	/**
	 * The main tick function, updates physical parameters
	 * and redraws the asteroid
	 */
	void update(float dt);

	/**
	 * Undraw the asteroid
	 */
	void destroy();

	/**
	 * Check if the asteroid is hit
	 * @return true if b is inside the asteroid
	 */
	bool isHit(point b);

	/**
	 * Split the asteroid into two asteroids
	 * Modifies this instance and returns a new one
	 * @return a new split asteroid
	 */
	Asteroid split();

	int size;
	int index;

private:
	vector2d vel;  // velocity
	vector2d acc;  // acceleration

	/** Initialize asteroid with random parameters */
	void initRand();
	/** Generate the random polygon representing the asteroid */
	void generate_polygon(int size);

	/** Physical parameter updates and drawing */
	void draw(uint16_t color);
	void updateAcceleration();
	void updateVelocity(float dt);
	void updateDisplacement(float dt);
};

#endif
