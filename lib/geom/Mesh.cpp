#include "Mesh.h"

void
Mesh::init(const VertexList& verts, const TetList& tets, double density)
{
    this->verts = verts;
    this->tets = tets;

    for (Tetrahedron& tet : this->tets) {
        tet.init(this->verts, density);
    }
}

double
Mesh::volume() const
{
    double result = 0;
    for (const Tetrahedron& t : tets) {
        result += t.volume();
    }
    return result;
}
