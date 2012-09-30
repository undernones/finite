#ifndef GEOMETRY_TETRAHEDRON_H
#define GEOMETRY_TETRAHEDRON_H

#include <Eigen>
#include <vector>
#include "Vertex.h"

namespace Geometry
{
    class Tetrahedron
    {
    public:
        uint32_t verts[4];
        Eigen::Matrix3d X;
        Eigen::Matrix3d Beta;
        
        Tetrahedron();
        Tetrahedron(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
        Tetrahedron(const Tetrahedron& other);
        ~Tetrahedron();

        Tetrahedron& operator =(const Tetrahedron& rhs);

        void init(const std::vector<Vertex>& vertices);

    private:
        Eigen::Vector3d u, v, w;
    };
}

#endif // GEOMETRY_TETRAHEDRON_H
