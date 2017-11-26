#include "asteroid.h"

void Asteroid::init(Adafruit_ILI9341* tft) {
	tft_ = tft;
	dx_ = 100;
	dy_ = 100;
	vx_ = -0.5;
	vy_ = -0.5;
	ax_ = 0;
	ay_ = 0;
}

void Asteroid::init(Adafruit_ILI9341* tft, float dx, float dy) {
	tft_ = tft;
	dx_ = dx;
	dy_ = dy;
	vx_ = -0.5;
	vy_ = -0.5;
	ax_ = 0;
	ay_ = 0;
}

void Asteroid::init(Adafruit_ILI9341* tft, float dx, float dy,
	float vx, float vy) {

	tft_ = tft;
	dx_ = dx;
	dy_ = dy;
	vx_ = vx;
	vy_ = vy;
	ax_ = 0;
	ay_ = 0;
}

void Asteroid::initRand(Adafruit_ILI9341* tft) {
	tft_ = tft;
	float sign;

	switch (random(4)) {
		case 0:
			dx_ = SPAWN_LEFT;
			dy_ = random(SPAWN_UP, SPAWN_DOWN+1);
			break;
		case 1:
			dx_ = SPAWN_RIGHT;
			dy_ = random(SPAWN_UP, SPAWN_DOWN+1);
			break;
		case 2:
			dx_ = random(SPAWN_LEFT, SPAWN_RIGHT+1);
			dy_ = SPAWN_UP;
			break;
		case 3:
			dx_ = random(SPAWN_LEFT, SPAWN_RIGHT+1);
			dy_ = SPAWN_DOWN;
			break;
	}

	sign = random(2)*2-1;
	vx_ = random(ASTEROID_VEL_MAG_MIN*100, ASTEROID_VEL_MAG_MAX*100+1);
	vx_ = vx_/100*sign;

	sign = random(2)*2-1;
	vy_ = random(ASTEROID_VEL_MAG_MIN*100, ASTEROID_VEL_MAG_MAX*100+1);
	vy_ = vy_/100*sign;

	ax_ = 0;
	ay_ = 0;

	point pt[4];

	pt[0].x = -BOX_LEN; pt[0].y = -BOX_LEN;
	pt[1].x = BOX_LEN; pt[1].y = -BOX_LEN;
	pt[2].x = BOX_LEN; pt[2].y = BOX_LEN;
	pt[3].x = -BOX_LEN; pt[3].y = BOX_LEN;

	edge_[0].p1 = pt[0];
	edge_[0].p2 = pt[1];

	edge_[1].p1 = pt[1];
	edge_[1].p2 = pt[2];

	edge_[2].p1 = pt[2];
	edge_[2].p2 = pt[3];

	edge_[3].p1 = pt[0];
	edge_[3].p2 = pt[3];
}

void Asteroid::updateAcceleration() {}

void Asteroid::updateVelocity() {
	vx_ += ax_;
	vy_ += ay_;
}

void Asteroid::updateDisplacement() {
	dx_ = constrain(dx_+vx_, LOOP_LEFT, LOOP_RIGHT);
	dy_ = constrain(dy_+vy_, LOOP_UP, LOOP_DOWN);

	if (dx_ == LOOP_LEFT) {
		dx_ = LOOP_RIGHT;
	}
	else if (dx_ == LOOP_RIGHT) {
		dx_ = LOOP_LEFT;
	}
	if (dy_ == LOOP_UP) {
		dy_ = LOOP_DOWN;
	}
	else if (dy_ == LOOP_DOWN) {
		dy_ = LOOP_UP;
	}
}

void Asteroid::update() {
	draw(ILI9341_BLACK);
	updateAcceleration();
	updateVelocity();
	updateDisplacement();
	draw(ASTEROID_COLOR);
}

void Asteroid::draw(uint16_t color) {
	for (int i = 0; i < NUM_EDGES; i++) {
		tft_->drawLine(edge_[i].p1.x+dx_, edge_[i].p1.y+dy_,
			edge_[i].p2.x+dx_, edge_[i].p2.y+dy_, color);
	}

	//tft_->drawCircle((uint16_t) dx_, (uint16_t) dy_, ASTEROID_RADIUS, color);
}

bool Asteroid::isHit(int bx, int by) {
	polygon ast;

	point center(dx_, dy_);
	ast.centroid = center;
	ast.edges = edge_;
	ast.nedges = NUM_EDGES;

	point p(bx, by);

	return ::is_collision(p, ast);
}
