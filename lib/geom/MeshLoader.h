#ifndef GEOM_MESHLOADER_H
#define GEOM_MESHLOADER_H

#include <string>

class Mesh;
class MeshLoader
{
public:
    static bool load(const std::string& filename, Mesh* pMesh, double density);

private:
    MeshLoader() {}
};

#endif // GEOM_MESHLOADER_H
