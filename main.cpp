#include <iostream>
#include <stdexcept>
#include <vector>
#include <Eigen>
#include "Utils.h"
#include "Tetrahedron.h"
#include "Mesh.h"
#include "MeshLoader.h"
#include "Options.h"

namespace
{

const int SUCCESS = 0;
const int ERROR = 1;

std::vector<Eigen::Matrix3d> sDeformations;
std::vector<Eigen::Matrix3d> sStrains;
std::vector<Eigen::Matrix3d> sStresses;


const std::vector<uint32_t>&
index2normals(uint32_t index)
{
    static std::vector<uint32_t> v[4];
    static bool firstTime = true;
    if (firstTime) {
        firstTime = false;

        v[0].push_back(0);
        v[0].push_back(1);
        v[0].push_back(2);

        v[1].push_back(0);
        v[1].push_back(3);
        v[1].push_back(1);

        v[2].push_back(0);
        v[2].push_back(2);
        v[2].push_back(3);

        v[3].push_back(1);
        v[3].push_back(3);
        v[3].push_back(2);
    }
    return v[index];
}

}

// --------------------------------------------------------------------------

void
step(Mesh *mesh, double dt)
{
    assert(mesh != NULL);

    std::vector<Tetrahedron>::const_iterator tet_it;
    std::vector<Eigen::Matrix3d>::iterator def_it;
    std::vector<Eigen::Matrix3d>::iterator strain_it;
    std::vector<Eigen::Matrix3d>::iterator stress_it;

    // Clear forces
    for (Vertex& v : mesh->verts) {
        v.f = Eigen::Vector3d(0, 0, 0);
    }

    // Deformation
    tet_it = mesh->tets.begin();
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

    // Internal Force
    stress_it = sStresses.begin();
    for (const Tetrahedron& tet : mesh->tets) {
        const uint32_t *verts = tet.vertices();
        for (int i = 0; i < 4; i++) {
            Eigen::Vector3d norms;
            for (uint32_t normIndex : index2normals(i)) {
                norms += tet.normals()[normIndex];
            }
            Vertex& vert = mesh->verts[verts[i]];
            vert.f += *stress_it * norms;
        }
    }


    // Integrate
    for (Vertex& v : mesh->verts) {
        Eigen::Vector3d a = v.f / v.mass;
        v.v += dt * a;
        v.x += dt * v.v;
    }
}
// --------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
    try {
        Options::init(&argc, &argv);

        Mesh mesh;
        if (!MeshLoader::load(Options::meshFile(), &mesh, Options::density())) {
            throw std::exception();
        }

        sDeformations.resize(mesh.tets.size());
        sStrains.resize(mesh.tets.size());
        sStresses.resize(mesh.tets.size());

        for (uint32_t i = 0; i < 120 * 50; ++i) {
            step(&mesh, Options::dt());
        }

        for (const Vertex& v : mesh.verts) {
            std::cout << "force:\n" << v.f << std::endl << std::endl;
        }
    } catch (std::exception &e) {
        Utils::error(std::string("Exception: ") + e.what());
        return ERROR;
    }

    return SUCCESS;
}
