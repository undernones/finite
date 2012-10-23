#include <iostream>
#include <stdexcept>
#include <vector>
#include <Eigen>
#include "Utils.h"
#include "Tetrahedron.h"
#include "Mesh.h"
#include "MeshLoader.h"
#include "Options.h"
#include "World.h"

using Eigen::Matrix3d;

namespace
{

const int SUCCESS = 0;
const int ERROR = 1;

}

int
main(int argc, char* argv[])
{
    try {
        Options::init(&argc, &argv);

        Mesh mesh;
        if (!MeshLoader::load(Options::meshFile(), &mesh, Options::density())) {
            throw std::exception();
        }

        World::init(&mesh);

        uint32_t totalSteps = Options::duration() / Options::dt();
        std::cout << "Duration:    " << Options::duration() << "s" << std::endl
                  << "Timestep:    " << Options::dt() << "s" << std::endl
                  << "Total steps: " << totalSteps << std::endl
                  << "Frames dir:  " << Options::framesDir() << std::endl
                  ;

        for (uint32_t i = 0; i < totalSteps; ++i) {
            World::step(Options::dt());
        }
    } catch (std::exception &e) {
        Utils::error(std::string("Exception: ") + e.what());
        return ERROR;
    }

    return SUCCESS;
}
// --------------------------------------------------------------------------
