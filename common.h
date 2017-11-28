#ifndef __COMMON_H__
#define __COMMON_H__

#include <Arduino.h>

#define TFT_WIDTH 320
#define TFT_HEIGHT 240

#ifndef PI
	#define PI 3.14159265
#endif

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

// Points are the same struct definition as 2d vectors
typedef vector2d point;

struct edge {
	point p1;
	point p2;

	edge() {}
	edge(point p1, point p2) : p1(p1), p2(p2) {}
};

struct polygon {
    point centroid;
    edge* edges;
    int sides;
};

bool on_screen(int x, int y);

// Collision between a point and a closed polygon
bool is_collision(point p, polygon poly);

class Asteroid;
class Bullet;
class Spaceship;

void spawn_asteroid(Asteroid* asteroid);
void spawn_bullet(Bullet* bullet);
void despawn_asteroid(Asteroid* asteroid);
void despawn_bullet(Bullet* bullet);

#endif
