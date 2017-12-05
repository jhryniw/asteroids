#include "spaceship.h"

Spaceship::Spaceship() {
  reset();

  verticesOrig[0] = {SPACESHIP_TRIANGLE_MAX, SPACESHIP_TRIANGLE_MAX};
  verticesOrig[1] = {SPACESHIP_TRIANGLE_MAX/4, SPACESHIP_TRIANGLE_MAX/3};
  verticesOrig[2] = {SPACESHIP_TRIANGLE_MAX/4, SPACESHIP_TRIANGLE_MAX/3};

  updateVertices();
}

Spaceship::~Spaceship() {
}

// State of ship at respawn
void Spaceship::reset() {
  pos = point(TFT_WIDTH/2, TFT_HEIGHT/2);
  u = point(0,1);
  becomeInvul(SPACESHIP_MAX_INVUL);
}

// Updates positions of ship triangle vertices
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

// Changes ship direction when joystick is moved
// Accelerates if button 1 is pressed
// Otherwise ship uses drag
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
		acc.x = sign(vel.x) * -50;
		acc.y = sign(vel.y) * -50;
	}
}

// Adds acceleration to velocity
// Magnitude is constrained
void Spaceship::updateVelocity(float dt) {
	vel.x = constrain(vel.x+acc.x*dt, -SPACESHIP_VEL_MAG_MAX, SPACESHIP_VEL_MAG_MAX);
	vel.y = constrain(vel.y+acc.y*dt, -SPACESHIP_VEL_MAG_MAX, SPACESHIP_VEL_MAG_MAX);
}

// Adds velocity to displacement
// Constrained within screen
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

// Counts down invincibility timer
void Spaceship::updateInvul(float dt) {
  if (invulTime < 0) {
    invul = false;
    invulTime = 0;
    spaceship_color = ILI9341_GREEN;
  }
  else if (invulTime > 0) {
    invulTime -= dt;
  }
}

// Sets invincibility timer
void Spaceship::becomeInvul(float time) {
  invul = true;
  invulTime = time;
  spaceship_color = ILI9341_CYAN;
}

// Returns if ship is invulnerable
bool Spaceship::isInvul() {
  return invul;
}

// Updates values and states of ship every frame
void Spaceship::update(float dt) {
	draw(ILI9341_BLACK);
	updateAcceleration();
	updateVelocity(dt);
	updateDisplacement(dt);
  updateInvul(dt);
	fire();
	draw(spaceship_color);
}

// Draws triangle using ship vertices
void Spaceship::draw(uint16_t color) {
  tft.drawTriangle((uint16_t) getVertexPos(0).x, (uint16_t) getVertexPos(0).y,
    (uint16_t) getVertexPos(1).x, (uint16_t) getVertexPos(1).y,
    (uint16_t) getVertexPos(2).x, (uint16_t) getVertexPos(2).y,
    color);
}

// Shoots bullet in direction of ship when button 2 is pressed
void Spaceship::fire() {
	if (getButtonPress(BUTTON_2, true)) {
		Bullet new_bullet(pos, u);
		::spawn_bullet(&new_bullet);
	}
}

// Returns coordinates of ship vertex at index
point Spaceship::getVertexPos(int index) {
  return vertices[index];
}
