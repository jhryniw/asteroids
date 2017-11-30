#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <Arduino.h>
#include "common.h"
#include "asteroid.h"
#include "spaceship.h"
#include "bullet.h"

#define MAX_ASTEROIDS 8
#define MAX_BULLETS 20
#define MAX_LIVES 3

class GameState {
public:
    GameState(Adafruit_ILI9341* tft);
    ~GameState();

    Spaceship spaceship;
    Asteroid* asteroids;
    Bullet* bullets;
    int score;
    int lives;

    void spawn(Asteroid* ast);
    void spawn(Bullet* bul);

    void despawn(Asteroid* ast);
    void despawn(Bullet* bul);

    void drawScore();
    void drawLives();

    void tick(float dt);

    bool hasMaxAsteroids();
    bool hasMaxBullets();

    int numAsteroids();
    int numBullets();

    void checkCollisions();

    void shipHit();
    void gameOver();

private:
    int ast_size_;
    int bul_size_;
    Adafruit_ILI9341* tft_;
};

extern GameState gameState;
extern float prevTime, deltaTime;

#endif
