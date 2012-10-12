#include <stdio.h>
#include <stdexcept>
#include "Utils.h"
#include "Vertex.h"
#include "Tetrahedron.h"
#include "Mesh.h"
#include "MeshLoader.h"

namespace
{

const int SUCCESS = 0;
const int ERROR = 1;

const double LAMBDA = 8000;
const double MU = 8000;

}

int
main(int argc, char* argv[])
{
    try {
        const char* meshFile = "meshes/cone.mesh";
        if (argc > 1) {
            meshFile = argv[1];
        }

        Mesh m;
        if (!MeshLoader::load(meshFile, &m)) {
            throw std::exception();
        }
        for (const Tetrahedron& t : m.tets) {
            Eigen::Matrix3d F = t.X() * t.Beta();
            Eigen::Matrix3d strain = 0.5 * (F + F.transpose()) - Eigen::Matrix3d::Identity();

            double d = LAMBDA * strain.trace();
            Eigen::Matrix3d diag;
            diag << d, 0, 0,
                    0, d, 0,
                    0, 0, d;
            Eigen::Matrix3d stress = 2 * MU * strain + diag;

            std::cout << "volume: " << t.volume() << std::endl;
        }
        std::cout << "total: " << m.volume() << std::endl
                  << "num tets: " << m.tets.size() << std::endl
                  ;
    } catch (std::exception &e) {
        Utils::error(std::string("Exception: ") + e.what());
        return ERROR;
    }

    return SUCCESS;
}
