#include "gameobject.h"

GameObject::GameObject()
{

}

void GameObject::tick()
{
    updateAcceleration();
    updateVelocity();
    updatePosition();
    draw();
}
