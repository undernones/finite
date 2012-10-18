#include <iostream>
#include <stdexcept>
#include <mutex>
#include <thread>
#include <vector>
#include <Eigen>
#include "Utils.h"
#include "Tetrahedron.h"
#include "Mesh.h"
#include "MeshLoader.h"
#include "Options.h"

//#define THREADS

namespace
{

const int SUCCESS = 0;
const int ERROR = 1;

std::mutex muxCout;

std::vector<Eigen::Matrix3d> sDeformations;
std::vector<Eigen::Matrix3d> sStrains;
std::vector<Eigen::Matrix3d> sStresses;

}

#ifdef THREADS
void
stuff(const std::vector<Tetrahedron>& tets, uint32_t lo, uint32_t hi)
{
    std::vector<Tetrahedron>::const_iterator beg = tets.begin() + lo;
    std::vector<Tetrahedron>::const_iterator end = tets.begin() + hi;
    std::vector<Tetrahedron>::const_iterator it;
    for (it = beg; it != end && it != tets.end(); ++it) {
        const Tetrahedron& t = *it;

        Eigen::Matrix3d F = t.X() * t.Beta();
        Eigen::Matrix3d strain = 0.5 * (F + F.transpose()) - Eigen::Matrix3d::Identity();

        double d = Options::lambda() * strain.trace();
        Eigen::Matrix3d diag;
        diag << d, 0, 0,
                0, d, 0,
                0, 0, d;
        Eigen::Matrix3d stress = 2 * Options::mu() * strain + diag;

#if 0
        {
            std::lock_guard<std::mutex> guard(muxCout);
            std::cout << "mat:\n" << stress << std::endl;
        }
#endif
    }
}
#endif

int
main(int argc, char* argv[])
{
    try {
        Options::init(&argc, &argv);

        Mesh m;
        if (!MeshLoader::load(Options::meshFile(), &m)) {
            throw std::exception();
        }

        sDeformations.resize(m.tets.size());
        sStrains.resize(m.tets.size());
        sStresses.resize(m.tets.size());

#ifdef THREADS
        const uint32_t threadCount = std::thread::hardware_concurrency();
        const uint32_t blockSize = m.tets.size() / threadCount;
        std::vector<std::thread> threads;
        for (uint32_t i = 0; i < threadCount; ++i) {
            uint32_t lo = i * blockSize;
            uint32_t hi = lo + blockSize - 1;
            threads.push_back(std::thread(stuff, m.tets, lo, hi));
        }
        for (std::thread& t : threads) {
            t.join();
        }
#else
        std::vector<Tetrahedron>::const_iterator tet_it;
        std::vector<Eigen::Matrix3d>::iterator def_it;
        std::vector<Eigen::Matrix3d>::iterator strain_it;
        std::vector<Eigen::Matrix3d>::iterator stress_it;

        // Deformation
        tet_it = m.tets.begin();
        def_it = sDeformations.begin();
        for (; def_it != sDeformations.end(); ++tet_it, ++def_it) {
            *def_it = tet_it->X() * tet_it->Beta();
        }

        // Strain
        def_it = sDeformations.begin();
        strain_it = sStrains.begin();
        for (; strain_it != sStrains.end(); ++def_it, ++strain_it) {
            const Eigen::Matrix3d& F = *def_it;
            *strain_it = 0.5 * (F + F.transpose()) - Eigen::Matrix3d::Identity();
        }

        // Stress
        def_it = sDeformations.begin();
        strain_it = sStrains.begin();
        stress_it = sStresses.begin();
        for (; stress_it != sStresses.end(); ++strain_it, ++def_it, ++stress_it) {
            const Eigen::Matrix3d& strain = *strain_it;
            const Eigen::Matrix3d& F = *def_it;

            double d = Options::lambda() * strain.trace();
            Eigen::Matrix3d diag;
            diag << d, 0, 0,
                    0, d, 0,
                    0, 0, d;
            *stress_it = F * (2 * Options::mu() * strain + diag);
        }
#endif

        std::cout << Options::friction() << std::endl;
    } catch (std::exception &e) {
        Utils::error(std::string("Exception: ") + e.what());
        return ERROR;
    }

    return SUCCESS;
}
