#include "gamestate.h"

float prevTime;
float deltaTime;

// Spawns an asteroid
void spawn_asteroid(Asteroid* asteroid) {
    gameState.spawn(asteroid);
}

// Spawns a bullet
void spawn_bullet(Bullet* bullet) {
    gameState.spawn(bullet);
}

// Despawns an asteroid
void despawn_asteroid(Asteroid* asteroid) {
    gameState.despawn(asteroid);
}

// Despawns a bullet
void despawn_bullet(Bullet* bullet) {
    gameState.despawn(bullet);
}

// Splits an asteroid into two, run on collision
void split_asteroid(Asteroid* asteroid) {
    if (asteroid->size <= 1) {
        despawn_asteroid(asteroid);
        return;
    }

    Asteroid new_ast = asteroid->split();
    spawn_asteroid(&new_ast);
}

// Initialize the gamestate
GameState::GameState(Adafruit_ILI9341* tft) :
    ast_size_(0), bul_size_(0), tft_(tft)
{
    asteroids = (Asteroid *) malloc(sizeof(Asteroid) * MAX_ASTEROIDS);
    bullets = (Bullet *) malloc(sizeof(Bullet) * MAX_BULLETS);
    score = 0;
    lives = MAX_LIVES;
}

// Destruct the gamestate
GameState::~GameState()
{
    free(asteroids);
    free(bullets);
}

// Spawn an asteroid
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

// Spawns a bullet
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

// Draw the score in the top left
void GameState::drawScore() {
  tft_->setCursor(10, 10);
  tft_->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft_->setTextSize(3);

  tft_->print(score);
}

// Draw the lives indicator in the top right
void GameState::drawLives() {
  for (int i = 0; i < lives; i++) {
    tft_->setCursor(TFT_WIDTH-30-20*i, 10);
    tft_->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft_->setTextSize(3);

    tft_->print((char) 3);
  }
}

// When the ship is hit, lose a life or the game
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

  if (lives <= 0) {
    gameOver();
  }
}

// Gets the number of digits
int getNumDigs(int num) {
  int count = 1;

  while (num /= 10) {
    count++;
  }

  return count;
}

// The Game Over screen
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

// The main game loop
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

// Despawns an asteroid
void GameState::despawn(Asteroid* ast)
{
    int index = ast->index;
    ast->destroy();

    // We can ONLY delete the edges here (on despawn)
    // Because then it isn't deleted on copy
    delete[] ast->edges;

    if (index != ast_size_ - 1) {
        // Swap in the last element
        asteroids[index] = asteroids[ast_size_ - 1];

        // Update the swapped index
        asteroids[index].index = index;
    }

    ast_size_--;
}

// Despawns a bullet
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

// Check for and handle collisions
void GameState::checkCollisions() {
  for(int i = 0; i < ast_size_; i++) {
      for(int j = 0; j < bul_size_; j++) {
          if(asteroids[i].isHit(bullets[j].getPosition())) {
              score += asteroids[i].size*100/3;
              split_asteroid(&asteroids[i]);
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

// Returns if the game state contains the maximum number of asteroids
bool GameState::hasMaxAsteroids()
{
    return ast_size_ >= MAX_ASTEROIDS;
}

// Returns if the game state contains the maximum number of bullets
bool GameState::hasMaxBullets()
{
    return bul_size_ >= MAX_BULLETS;
}

// Returns the number of asteroids in the game state
int GameState::numAsteroids()
{
    return ast_size_;
}

// Returns the number of bullets in the game state
int GameState::numBullets()
{
    return bul_size_;
}
