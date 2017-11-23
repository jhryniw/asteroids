#include "gamestate.h"

void spawn_asteroid(Asteroid* asteroid) {
    gameState.spawn(asteroid);
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

GameState::GameState() :
    ast_size_(0), bul_size_(0)
{
    asteroids = new Asteroid[MAX_ASTEROIDS];
    bullets = new Bullet[MAX_BULLETS];
}

GameState::~GameState()
{
    delete[] asteroids;
    delete[] bullets;
}

void GameState::spawn(Asteroid* ast)
{
    if (ast_size_ >= MAX_ASTEROIDS) {
        Serial.print("Cannot add another asteroid, game state is full!");
        return;
    }

    ast->index = ast_size_;
    asteroids[ast_size_] = *ast;
    ast_size_++;
}

void GameState::spawn(Bullet* bul)
{
    if (bul_size_ >= MAX_BULLETS) {
        Serial.print("Cannot add another asteroid, game state is full!");
        return;
    }

    bul->index = bul_size_;
    bullets[bul_size_] = *bul;
    bul_size_++;
}

void GameState::tick()
{
    spaceship.update();

    for(int i = 0; i < ast_size_; i++) {
        asteroids[i].update();
    }

    for(int i = 0; i < bul_size_; i++) {
        bullets[i].update();
    }
}

void GameState::despawn(Asteroid* ast)
{
    int index = ast->index;

    if (index != bul_size_ - 1) {
        // Swap in the last element
        asteroids[index] = asteroids[bul_size_ - 1];

        // Update the swapped index
        asteroids[index].index = index;
    }

    ast_size_--;
}

void GameState::despawn(Bullet* bul)
{
    int index = bul->index;

    if (index != bul_size_ - 1) {
        // Swap in the last element
        bullets[index] = bullets[bul_size_ - 1];

        // Update the swapped index
        bullets[index].index = index;
    }

    bul_size_--;
}
