#include "Mesh.h"

void
Mesh::init(const std::vector<Vertex>& verts, const std::vector<Tetrahedron>& tets)
{
    this->verts = verts;
    this->tets = tets;

    for (Tetrahedron& tet : this->tets) {
        tet.init(this->verts);
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
