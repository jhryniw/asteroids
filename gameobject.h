#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <Arduino.h>

#define MAX_OBJECTS = 10;

class GameState;

class GameObject {
    friend class GameState;

public:
    GameObject();
    virtual ~GameObject();

    void tick();

protected:
    virtual void draw();
    virtual void updateAcceleration();
    virtual void updateVelocity();
    virtual void updatePosition();

private:
    int index_;
};

#endif
