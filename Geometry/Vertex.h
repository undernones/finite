#ifndef GEOMETRY_VERTEX_H
#define GEOMETRY_VERTEX_H

#include <Eigen>
#include <vector>

namespace Geometry
{
    class Vertex
    {
    public:
        Eigen::Vector3d x; // world position
        Eigen::Vector3d u; // material position
        Eigen::Vector3d v; // velocity
        Eigen::Vector3d f; // forces

        double mass;

        Vertex();
        Vertex(const Vertex& other);
        ~Vertex() {}

        Vertex& operator =(const Vertex& rhs);
    };

    typedef std::vector<Vertex> VertexList ;
}

#endif // GEOMETRY_VERTEX_H
