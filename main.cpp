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
        for (const Tetrahedron& t : m.tets) {
            std::cout << t.verts[0] << ", "
                      << t.verts[1] << ", "
                      << t.verts[2] << ", "
                      << t.verts[3] << std::endl;
            Eigen::Matrix3d F = t.X * t.Beta;
            std::cout << "X: " << std::endl << t.X << std::endl
                      << "Beta: " << std::endl << t.Beta << std::endl
                      << "F: " << std::endl << F << std::endl
                      << std::endl;
        }
        printf("Hello, world!\n");
    } catch (std::exception &e) {
        Utils::error(std::string("Exception: ") + e.what());
        return ERROR;
    }

    return SUCCESS;
}
