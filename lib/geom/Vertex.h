#ifndef GEOMETRY_VERTEX_H
#define GEOMETRY_VERTEX_H

#include <Eigen>
#include <vector>

class Vertex
{
public:
    Eigen::Vector3d x; // world position
    Eigen::Vector3d u; // material position
    Eigen::Vector3d v; // velocity
    Eigen::Vector3d f; // forces

    double mass;
    uint32_t index;

    Vertex();
    ~Vertex() {}
};

typedef std::vector<Vertex> VertexList;

#endif // GEOMETRY_VERTEX_H
