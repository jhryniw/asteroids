#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <Arduino.h>
#include "common.h"
#include "asteroid.h"
#include "spaceship.h"
#include "bullet.h"

#define MAX_ASTEROIDS 8
#define MAX_BULLETS 10
#define MAX_LIVES 3

/**
 * Represents the Game
 */
class GameState {
public:
    GameState(Adafruit_ILI9341* tft);
    ~GameState();

    Spaceship spaceship;
    Asteroid* asteroids;
    Bullet* bullets;
    int score;
    int lives;

    // Add objects to the game state
    void spawn(Asteroid* ast);
    void spawn(Bullet* bul);

    // Remove objects from the game state
    void despawn(Asteroid* ast);
    void despawn(Bullet* bul);

    // Draw the lives and score on screen
    void drawScore();
    void drawLives();

    // The main game loop
    void tick(float dt);

    // Query if game state is full of asteroids
    bool hasMaxAsteroids();
    // Query if game state is full of bullets
    bool hasMaxBullets();

    // Query number of asteroids in the game
    int numAsteroids();
    // Query number of bullets in the game
    int numBullets();

    // Check for collisions
    void checkCollisions();

    // Handle if the ship is hit
    void shipHit();
    // Handle the game ending
    void gameOver();

private:
    int ast_size_;
    int bul_size_;
    Adafruit_ILI9341* tft_;
};

extern GameState gameState;
extern float prevTime, deltaTime;

#endif
