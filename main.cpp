#include <stdio.h>
#include "Utils.h"
#include "Geometry/Vertex.h"
#include "Geometry/Tetrahedron.h"
#include "Geometry/Mesh.h"
#include "Geometry/MeshLoader.h"

namespace
{

const int SUCCESS = 0;
const int ERROR = 1;

}

using namespace Geometry;

int
main(int arcg,char * argv[])
{
    try {
        Mesh m;
        if (!MeshLoader::load("meshes/cone.mesh", &m)) {
            printf("badness\n");
            return ERROR;
        }
        printf("Hello, world!\n");
    } catch (std::exception &e) {
        Utils::error(std::string("Exception: ") + e.what());
        return ERROR;
    }

    return SUCCESS;
}
