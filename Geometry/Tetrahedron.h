#ifndef GEOMETRY_TETRAHEDRON_H
#define GEOMETRY_TETRAHEDRON_H

#include <Eigen>
#include "Vertex.h"

namespace Geometry
{
    class Tetrahedron
    {
    public:
        uint32_t verts[4];
        
        Tetrahedron(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
        Tetrahedron(const Tetrahedron& other);
        ~Tetrahedron();

        Tetrahedron& operator =(const Tetrahedron& rhs);

        void init(const VertexList& vertices);

        const Eigen::Matrix3d& updateX(const VertexList& vertices);
        const Eigen::Matrix3d& X() const { return mX; }

        const Eigen::Matrix3d& Beta() const { return mBeta; }
        const Eigen::Matrix3d& updateBeta(const VertexList& vertices);

        double volume() const { return mVolume; }

    private:
        Eigen::Vector3d u, v, w;
        Eigen::Matrix3d mX;
        Eigen::Matrix3d mBeta;
        double mVolume;

        void computeVolume();
    };
}

#endif // GEOMETRY_TETRAHEDRON_H
