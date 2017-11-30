#include "gamestate.h"

float prevTime;
float deltaTime;

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
    lives = MAX_LIVES;
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

void GameState::drawLives() {
  for (int i = 0; i < lives; i++) {
    tft_->setCursor(TFT_WIDTH-30-20*i, 10);
    tft_->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft_->setTextSize(3);

    tft_->print((char) 3);
  }
}

void GameState::shipHit() {
  delay(500);
  prevTime = millis();
  deltaTime = (millis() - prevTime) / 1000;

  lives--;
  spaceship.reset();

  tft_->setCursor(TFT_WIDTH-30-20*lives, 10);
  tft_->setTextColor(ILI9341_BLACK);
  tft_->setTextSize(3);
  tft_->print((char) 3);

  if (lives < 0) {
    gameOver();
  }
}

int getNumDigs(int num) {
  int count = 1;

  while (num /= 10) {
    count++;
  }

  return count;
}

void GameState::gameOver() {
  tft.fillScreen(ILI9341_BLACK);
  tft_->setTextColor(ILI9341_WHITE);
  tft_->setTextSize(3);

  tft_->setCursor(TFT_WIDTH/2-15*12/2, TFT_HEIGHT/2-40);
  tft_->print("Game over!");

  tft_->setCursor(TFT_WIDTH/2-15*13/2, TFT_HEIGHT/2);
  tft_->print("Your score:");

  tft_->setCursor(TFT_WIDTH/2-15*(getNumDigs(score)+2)/2, TFT_HEIGHT/2+40);
  tft_->print(score);

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

    drawScore();
    drawLives();
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
      for (int k = 0; k < 3 && !spaceship.isInvul(); k++) {
        if(asteroids[i].isHit(spaceship.getVertexPos(k))) {
          shipHit();
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
