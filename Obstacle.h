#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Vertex.h"

class Obstacle
{
public:
    Obstacle();
    Obstacle(double friction);
    virtual ~Obstacle();
    virtual bool bounce(Vertex& v) const = 0;
    virtual void draw() const {}

    inline double friction() const { return mFriction; }
    inline void setFriction(double f) { mFriction = f; }

protected:
    double mFriction;
};

#endif // OBSTACLE_H

