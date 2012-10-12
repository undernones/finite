#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vertex.h"
#include "Tetrahedron.h"

class Mesh
{
public:
    std::vector<Vertex> verts;
    std::vector<Tetrahedron> tets;

    void init(const std::vector<Vertex>& verts, const std::vector<Tetrahedron>& tets);
    double volume() const;
};

#endif // MESH_H
