#include "asteroid.h"

Asteroid::Asteroid()
	: polygon()
{
	initRand();
}

Asteroid::~Asteroid()
{

}

void Asteroid::initRand() {
	sides = floor(random(4, 7));

	edges = new edge[sides];
	generate_polygon(1);

	float sign;

	switch (random(4)) {
		case 0:
			centroid.x = SPAWN_LEFT;
			centroid.y = random(SPAWN_UP, SPAWN_DOWN+1);
			break;
		case 1:
			centroid.x = SPAWN_RIGHT;
			centroid.y = random(SPAWN_UP, SPAWN_DOWN+1);
			break;
		case 2:
			centroid.x = random(SPAWN_LEFT, SPAWN_RIGHT+1);
			centroid.y = SPAWN_UP;
			break;
		case 3:
			centroid.x = random(SPAWN_LEFT, SPAWN_RIGHT+1);
			centroid.y = SPAWN_DOWN;
			break;
	}

	sign = random(2)*2-1;
	vel.x = random(ASTEROID_VEL_MAG_MIN*100, ASTEROID_VEL_MAG_MAX*100+1);
	vel.x = vel.x/100*sign;

	sign = random(2)*2-1;
	vel.y = random(ASTEROID_VEL_MAG_MIN*100, ASTEROID_VEL_MAG_MAX*100+1);
	vel.y = vel.y/100*sign;

	size = 3;
}

void Asteroid::updateAcceleration() {}

void Asteroid::updateVelocity() {
	vel.x += acc.x;
	vel.y += acc.y;
}

void Asteroid::updateDisplacement() {
	centroid.x = constrain(centroid.x+vel.x, LOOP_LEFT, LOOP_RIGHT);
	centroid.y = constrain(centroid.y+vel.y, LOOP_UP, LOOP_DOWN);

	if (centroid.x == LOOP_LEFT) {
		centroid.x = LOOP_RIGHT;
	}
	else if (centroid.x == LOOP_RIGHT) {
		centroid.x = LOOP_LEFT;
	}
	if (centroid.y == LOOP_UP) {
		centroid.y = LOOP_DOWN;
	}
	else if (centroid.y == LOOP_DOWN) {
		centroid.y = LOOP_UP;
	}
}

void Asteroid::generate_polygon(int size) {
	// Generates a random closed polygon
	float angular_step = 2 * PI / (float) sides;

	point first_point, last_point;

	for (int v = 0; v < sides; v++) {
		int rand_num = random(20, 40);
		float vertex_size = rand_num*rand_num/100*size;
		float vertex_angle = angular_step * v + angular_step / 3 * random(1);

		if (v == 0) {
			first_point = last_point = point(vertex_size * cos(vertex_angle), vertex_size * sin(vertex_angle));
		}
		else {
			point next_point = point(vertex_size * cos(vertex_angle), vertex_size * sin(vertex_angle));
			edges[v-1] = edge(last_point, next_point);
			last_point = next_point;
		}
	}

	edges[sides - 1] = edge(last_point, first_point);
}

void Asteroid::update() {
	draw(ILI9341_BLACK);
	updateAcceleration();
	updateVelocity();
	updateDisplacement();
	draw(ASTEROID_COLOR);
}

void Asteroid::destroy() {
	draw(ILI9341_BLACK);
}

void Asteroid::draw(uint16_t color) {
	for (int i = 0; i < sides; i++) {
		tft.drawLine(edges[i].p1.x+centroid.x, edges[i].p1.y+centroid.y,
			edges[i].p2.x+centroid.x, edges[i].p2.y+centroid.y, color);
	}
}

bool Asteroid::isHit(point b) {
	return ::is_collision(b, *this);
}
