#include "gamestate.h"

GameState::GameState(int max_size) :
    max_size_(max_size), size_(0)
{
    objs_ = new GameObject[max_size];
}

GameState::~GameState()
{
    delete[] objs_;
}

void GameState::spawn(GameObject* obj)
{
    if (size_ >= max_size_) {
        Serial.print("Cannot add another object, game state is full!");
        return;
    }

    obj->index_ = size_;
    objs_[size_] = *obj;
    size_++;
}

void GameState::tick()
{
    for(int i = 0; i < size_; i++) {
        objs_[i].tick();
    }
}

void swap(GameObject* a, GameObject* b) {
    GameObject temp = *a;
    *a = *b;
    *b = temp;
}

void GameState::despawn(GameObject* obj)
{
    int index = obj->index_;

    // Swap in the last element
    swap(&objs_[index], &objs_[size_ - 1]);

    // Update the swapped index
    objs_[index].index_ = index;

    // Delete the object
    delete obj;

    size_--;
}

int GameState::size()
{
    return size_;
}
