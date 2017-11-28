#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <Arduino.h>
#include "common.h"
#include "asteroid.h"
#include "spaceship.h"
#include "bullet.h"

#define MAX_ASTEROIDS 20
#define MAX_BULLETS 10

class GameState {
public:
    GameState();
    ~GameState();

    Spaceship spaceship;
    Asteroid* asteroids;
    Bullet* bullets;

    void spawn(Asteroid* ast);
    void spawn(Bullet* bul);

    void tick();

    void despawn(Asteroid* ast);
    void despawn(Bullet* bul);

private:
    int ast_size_;
    int bul_size_;
    
};

extern GameState gameState;

#endif
