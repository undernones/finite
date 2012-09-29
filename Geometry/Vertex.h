#ifndef GEOMETRY_VERTEX_H
#define GEOMETRY_VERTEX_H

#include <Eigen>

class Vertex
{
public:
    Eigen::Vector3d x; // position
    Eigen::Vector3d v; // velocity
    Eigen::Vector3d f; // forces

    double mass;

    Vertex();
    Vertex(const Vertex& other);
    ~Vertex() {}

    Vertex& operator =(const Vertex& rhs);
};

#endif // GEOMETRY_VERTEX_H
