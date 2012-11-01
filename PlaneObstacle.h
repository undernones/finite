#ifndef PLANE_OBSTACLE_H
#define PLANE_OBSTACLE_H

#include "Obstacle.h"
#include <Eigen>

class PlaneObstacle : public Obstacle
{
public:
    PlaneObstacle();
    PlaneObstacle(const Eigen::Vector3d& normal, double offset, double friction);
    ~PlaneObstacle();

    virtual bool bounce(Vertex& particle) const;
    virtual void draw() const;

private:
    Eigen::Vector3d mNormal;
    double mOffset;
};

#endif // PLANE_OBSTACLE_H

