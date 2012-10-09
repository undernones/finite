#ifndef GEOMETRY_MESH_H
#define GEOMETRY_MESH_H

#include <vector>
#include "Vertex.h"
#include "Tetrahedron.h"

namespace Geometry
{
    class Mesh
    {
    public:
        std::vector<Vertex> verts;
        std::vector<Tetrahedron> tets;

        void init(const std::vector<Vertex>& verts, const std::vector<Tetrahedron>& tets);
        double volume() const;
    };
}

#endif // GEOMETRY_MESH_H
