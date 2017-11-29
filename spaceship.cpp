#include "spaceship.h"

Spaceship::Spaceship()
 : pos(TFT_WIDTH/2, TFT_HEIGHT/2), u(0, 1)
{
  verticesOrig[0] = {SPACESHIP_TRIANGLE_MAX, SPACESHIP_TRIANGLE_MAX};
  verticesOrig[1] = {SPACESHIP_TRIANGLE_MAX/4, SPACESHIP_TRIANGLE_MAX/3};
  verticesOrig[2] = {SPACESHIP_TRIANGLE_MAX/4, SPACESHIP_TRIANGLE_MAX/3};

  updateVertices();
}

Spaceship::~Spaceship()
{

}

void Spaceship::updateVertices() {
  float nx = u.y;
  float ny = -u.x;
  float norm_mag = sqrt(nx*nx+ny*ny);

  nx /= norm_mag;
  ny /= norm_mag;

  vertices[0] = {pos.x-u.x*SPACESHIP_TRIANGLE_OFFSET+verticesOrig[0].x*u.x,
    pos.y-u.y*SPACESHIP_TRIANGLE_OFFSET+verticesOrig[0].y*u.y};
  vertices[1] = {pos.x-u.x*SPACESHIP_TRIANGLE_OFFSET+verticesOrig[1].x*nx,
    pos.y-u.y*SPACESHIP_TRIANGLE_OFFSET+verticesOrig[1].y*ny};
  vertices[2] = {pos.x-u.x*SPACESHIP_TRIANGLE_OFFSET+verticesOrig[2].x*-nx,
    pos.y-u.y*SPACESHIP_TRIANGLE_OFFSET+verticesOrig[2].y*-ny};
}

void Spaceship::updateAcceleration() {
	float ux = getJoystickHoriz();
	float uy = getJoystickVert();

	float magnitude = sqrt(ux*ux+uy*uy);
	if (magnitude != 0) {
		ux = ux/magnitude;
		uy = uy/magnitude;
		u = vector2d(ux, uy);
    updateVertices();
	}

	if (getButtonPress(BUTTON_1, false)) {
		acc.x = u.x*SPACESHIP_ACC_MAG;
		acc.y = u.y*SPACESHIP_ACC_MAG;
	}
	else {
		acc.x = sign(vel.x) * -0.01;
		acc.y = sign(vel.y) * -0.01;
	}
}

void Spaceship::updateVelocity(float dt) {
	vel.x = constrain(vel.x+acc.x*dt, -SPACESHIP_VEL_MAG_MAX, SPACESHIP_VEL_MAG_MAX);
	vel.y = constrain(vel.y+acc.y*dt, -SPACESHIP_VEL_MAG_MAX, SPACESHIP_VEL_MAG_MAX);
}

void Spaceship::updateDisplacement(float dt) {
	pos.x = constrain(pos.x+vel.x*dt, 0, TFT_WIDTH);
	pos.y = constrain(pos.y+vel.y*dt, 0, TFT_HEIGHT);

	if (pos.x == 0 || pos.x == TFT_WIDTH) {
		vel.x = 0;
		acc.x = 0;
	}
	if (pos.y == 0 || pos.y == TFT_HEIGHT) {
		vel.y = 0;
		acc.y = 0;
	}
  updateVertices();
}

void Spaceship::update(float dt) {
	draw(ILI9341_BLACK);
	updateAcceleration();
	updateVelocity(dt);
	updateDisplacement(dt);
	fire();
	draw(SPACESHIP_COLOR);
}

void Spaceship::draw(uint16_t color) {

	tft.drawCircle((uint16_t) pos.x, (uint16_t) pos.y, SPACESHIP_RADIUS, color);
  /*
	tft.drawLine((uint16_t) pos.x, (uint16_t) pos.y,
		(uint16_t) pos.x+u.x*SPACESHIP_RADIUS,
			(uint16_t) pos.y+u.y*SPACESHIP_RADIUS, color);
  */
  tft.drawTriangle((uint16_t) getVertexPos(0).x, (uint16_t) getVertexPos(0).y,
    (uint16_t) getVertexPos(1).x, (uint16_t) getVertexPos(1).y,
    (uint16_t) getVertexPos(2).x, (uint16_t) getVertexPos(2).y,
    color);
}

void Spaceship::fire() {
	if (getButtonPress(BUTTON_2, true)) {
		Bullet new_bullet(pos, u);
		::spawn_bullet(&new_bullet);
	}
}

point Spaceship::getVertexPos(int index) {
  return vertices[index];
  // point p (vertices[index].x+pos.x, vertices[index].y+pos.y);
  // return p;
}
