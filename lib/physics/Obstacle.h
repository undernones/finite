#ifndef PHYSICS_OBSTACLE_H
#define PHYSICS_OBSTACLE_H

#include <geom/Vertex.h>

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

#endif // PHYSICS_OBSTACLE_H

