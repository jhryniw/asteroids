#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <Arduino.h>
#include "gameobject.h"

class GameState {
public:
    GameState(int max_size);
    ~GameState();

    void spawn(GameObject* obj);
    void tick();
    void despawn(GameObject* obj);
    int size();

private:
    int max_size_;
    int size_;

    GameObject* objs_;
};

#endif
