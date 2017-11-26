#ifndef __COMMON_H__
#define __COMMON_H__

#include <Arduino.h>

#define TFT_WIDTH 320
#define TFT_HEIGHT 240

struct point {
	int x;
	int y;

    point() : x(0), y(0) {};
    point(int x, int y) : x(x), y(y) {}
};

struct edge {
	point p1;
	point p2;
};

struct polygon {
    point centroid;
    edge* edges;
    int nedges;
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
