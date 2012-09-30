#include "Mesh.h"

namespace Geometry
{

void
Mesh::init(const std::vector<Vertex>& verts, const std::vector<Tetrahedron>& tets)
{
    this->verts = verts;
    this->tets = tets;

    for (Tetrahedron& tet : this->tets) {
        tet.init(this->verts);
    }
}

}
