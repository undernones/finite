#include "PlaneObstacle.h"

PlaneObstacle::PlaneObstacle() :
    mNormal()
{
    mOffset = 0;
}

PlaneObstacle::PlaneObstacle(const Eigen::Vector3d& normal, double offset, double friction) :
    Obstacle(friction),
    mNormal(normal),
    mOffset(offset)
{
    mNormal.normalize();
}

PlaneObstacle::~PlaneObstacle()
{
}

bool
PlaneObstacle::bounce(Vertex& vert) const
{
    double d = vert.x.dot(mNormal);
    if (d > mOffset) return false;

    // Project the vert's position onto the surface of the obstacle.
    vert.x += (mOffset - d) * mNormal;

    // Split the vert's velocity into normal and tangential components.
    double normMag = vert.v.dot(mNormal);
    Eigen::Vector3d normVel = normMag * mNormal;
    Eigen::Vector3d tanVel = vert.v - normVel;

    vert.v = (1.0 - friction()) * tanVel;
    return true;
}

void
PlaneObstacle::draw() const
{
}

