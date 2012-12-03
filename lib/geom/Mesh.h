#ifndef GEOM_MESH_H
#define GEOM_MESH_H

#include <vector>
#include "Vertex.h"
#include "Tetrahedron.h"

class Mesh
{
public:
    VertexList verts;
    std::vector<Tetrahedron> tets;

    void init(const VertexList& verts, const TetList& tets, double density);
    double volume() const;
};

#endif // GEOM_MESH_H
