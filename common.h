#ifndef __COMMON_H__
#define __COMMON_H__

#define TFT_WIDTH 320
#define TFT_HEIGHT 240

class Asteroid;
class Bullet;
class Spaceship;

bool on_screen(int x, int y);

void spawn_asteroid(Asteroid* asteroid);
void spawn_bullet(Bullet* bullet);
void despawn_asteroid(Asteroid* asteroid);
void despawn_bullet(Bullet* bullet);

#endif
