#ifndef __COMMON_H__
#define __COMMON_H__

#include <Arduino.h>

#define TFT_WIDTH 320
#define TFT_HEIGHT 240

#ifndef PI
	#define PI 3.14159265
#endif

/*
 * Return the sign of value
 */
template <typename T>
T sign(T value) {
	return T((value>0)-(value<0));
}

struct vector2d {
	float x;
	float y;

    vector2d() : x(0), y(0) {}
    vector2d(float x, float y) : x(x), y(y) {}
};

/** Points are the same struct definition as 2d vectors */
typedef vector2d point;

/** Represents an edge object, a line between two points */
struct edge {
	point p1;
	point p2;

	// Empty Constructor
	edge() {}
	edge(point p1, point p2) : p1(p1), p2(p2) {}
};

/**
 * Represents a polygon, is the building block for
 * more complex game objects
 */
struct polygon {
    point centroid;
    edge* edges;
    int sides;
};

/**
 * Check if a point is on the screen
 * @param x x coordinate
 * @param y y coordinate
 * @return true if point is on the screen
 */
bool on_screen(int x, int y);

// Collision between a point and a closed polygon
bool is_collision(point p, polygon poly);

/**
 * Prototypes for global game state functions
 */
class Asteroid;
class Bullet;
class Spaceship;

void spawn_asteroid(Asteroid* asteroid);   // Adds an asteroid into the game state
void spawn_bullet(Bullet* bullet);         // Adds a bullet into the game state
void despawn_asteroid(Asteroid* asteroid); // Removes an asteroid from the game state
void despawn_bullet(Bullet* bullet);       // Removes a bullet from the game state

#endif
