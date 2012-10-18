#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include <string>

class Mesh;
class MeshLoader
{
public:
    static bool load(const std::string& filename, Mesh* pMesh);

private:
    MeshLoader() {}
};

#endif // MESH_LOADER_H
