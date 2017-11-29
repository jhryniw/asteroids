#include "gamestate.h"

void spawn_asteroid(Asteroid* asteroid) {
    gameState.spawn(asteroid);
    //Serial.println(asteroid->index);
}

void spawn_bullet(Bullet* bullet) {
    gameState.spawn(bullet);
}

void despawn_asteroid(Asteroid* asteroid) {
    gameState.despawn(asteroid);
}

void despawn_bullet(Bullet* bullet) {
    gameState.despawn(bullet);
}

/*template<class T>
void swap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}*/

GameState::GameState(Adafruit_ILI9341* tft) :
    ast_size_(0), bul_size_(0), tft_(tft)
{
    asteroids = (Asteroid *) malloc(sizeof(Asteroid) * MAX_ASTEROIDS);
    bullets = (Bullet *) malloc(sizeof(Bullet) * MAX_BULLETS);
    score = 0;
    lives = 3;
}

GameState::~GameState()
{
    free(asteroids);
    free(bullets);
}

void GameState::spawn(Asteroid* ast)
{
    if (ast_size_ >= MAX_ASTEROIDS) {
        //Serial.print("Cannot add another asteroid, game state is full!");
        return;
    }

    ast->index = ast_size_;
    asteroids[ast_size_] = *ast;
    ast_size_++;
}

void GameState::spawn(Bullet* bul)
{
    if (bul_size_ >= MAX_BULLETS) {
        //Serial.print("Cannot add another asteroid, game state is full!");
        return;
    }

    bul->index = bul_size_;
    bullets[bul_size_] = *bul;
    bul_size_++;
}

void GameState::drawScore() {
  tft_->setCursor(10, 10);
  tft_->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft_->setTextSize(3);

  tft_->print(score);
}

void GameState::gameOver() {
  while (true) {}
}

void GameState::tick(float dt)
{
    spaceship.update(dt);

    for(int i = 0; i < ast_size_; i++) {
        asteroids[i].update(dt);
    }

    for(int i = 0; i < bul_size_; i++) {
        bullets[i].update(dt);
    }

    checkCollisions();

    if (lives <= 0) {
      gameOver();
    }

    drawScore();
}

void GameState::despawn(Asteroid* ast)
{
    int index = ast->index;
    ast->destroy();

    if (index != ast_size_ - 1) {
        // Swap in the last element
        asteroids[index] = asteroids[ast_size_ - 1];

        // Update the swapped index
        asteroids[index].index = index;
    }

    ast_size_--;
}

void GameState::despawn(Bullet* bul)
{
    int index = bul->index;
    bul->destroy();

    if (index != bul_size_ - 1) {
        // Swap in the last element
        bullets[index] = bullets[bul_size_ - 1];

        // Update the swapped index
        bullets[index].index = index;
    }

    bul_size_--;
}

void GameState::checkCollisions() {
  for(int i = 0; i < ast_size_; i++) {
      for(int j = 0; j < bul_size_; j++) {
          if(asteroids[i].isHit(bullets[j].getPosition())) {
              score += asteroids[i].size*100/3;
              despawn(&asteroids[i]);
              despawn(&bullets[j]);
              break;
          }
      }
      for (int k = 0; k < 3; k++) {
        if(asteroids[i].isHit(spaceship.getVertexPos(k))) {
          lives--;
        }
      }
  }

}

bool GameState::hasMaxAsteroids()
{
    return ast_size_ >= MAX_ASTEROIDS;
}

bool GameState::hasMaxBullets()
{
    return bul_size_ >= MAX_BULLETS;
}

int GameState::numAsteroids()
{
    return ast_size_;
}

int GameState::numBullets()
{
    return bul_size_;
}
