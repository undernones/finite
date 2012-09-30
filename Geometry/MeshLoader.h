#ifndef GEOMETRY_MESH_LOADER_H
#define GEOMETRY_MESH_LOADER_H

#include "Mesh.h"

namespace Geometry
{
    class Mesh;
    class MeshLoader
    {
    public:
        static bool load(const std::string& filename, Geometry::Mesh* pMesh);

    private:
        MeshLoader() {}
    };
}

#endif // MESH_LOADER_H
