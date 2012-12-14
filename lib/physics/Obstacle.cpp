#include "Obstacle.h"

Obstacle::Obstacle() :
    Obstacle(0.05)
{
}

Obstacle::Obstacle(double friction) :
    mFriction(friction)
{
}

Obstacle::~Obstacle()
{
}
