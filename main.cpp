#include <iostream>
#include <stdexcept>
#include <vector>
#include <Eigen>
#include "Utils.h"
#include "Tetrahedron.h"
#include "Mesh.h"
#include "MeshLoader.h"
#include "Options.h"

using Eigen::Matrix3d;

namespace
{

const int SUCCESS = 0;
const int ERROR = 1;

std::vector<Matrix3d> sDeformations;
std::vector<Matrix3d> sStrains;
std::vector<Matrix3d> sStresses;

}

// --------------------------------------------------------------------------

void
computeDeformations(const std::vector<Tetrahedron>& tets,
                    std::vector<Matrix3d>& deformations)
{
    std::vector<Tetrahedron>::const_iterator tet_it = tets.begin();
    std::vector<Matrix3d>::iterator def_it = deformations.begin();
    for (; def_it != deformations.end(); ++tet_it, ++def_it) {
        *def_it = tet_it->X() * tet_it->Beta();
    }
}
// --------------------------------------------------------------------------

void
computeStrains(const std::vector<Matrix3d>& deformations,
               std::vector<Matrix3d>& strains)
{
    std::vector<Matrix3d>::const_iterator def_it = deformations.begin();
    std::vector<Matrix3d>::iterator strain_it = strains.begin();
    for (; strain_it != strains.end(); ++def_it, ++strain_it) {
        const Matrix3d& F = *def_it;
        // Linear Cauchy strain
        *strain_it = 0.5 * (F + F.transpose()) - Matrix3d::Identity();
    }
}
// --------------------------------------------------------------------------

void
computeStresses(const std::vector<Matrix3d>& deformations,
                const std::vector<Matrix3d>& strains,
                std::vector<Matrix3d>& stresses)
{
    std::vector<Matrix3d>::const_iterator def_it = deformations.begin();
    std::vector<Matrix3d>::const_iterator strain_it = strains.begin();
    std::vector<Matrix3d>::iterator stress_it = stresses.begin();
    for (; stress_it != sStresses.end(); ++strain_it, ++def_it, ++stress_it) {
        const Matrix3d& strain = *strain_it;
        const Matrix3d& F = *def_it;

        double d = Options::lambda() * strain.trace();
        Matrix3d diag;
        diag << d, 0, 0,
                0, d, 0,
                0, 0, d;
        *stress_it = F * (2 * Options::mu() * strain + diag);
    }
}
// --------------------------------------------------------------------------

void
computeForces(const std::vector<Matrix3d>& stresses, Mesh *mesh)
{
    assert(mesh != NULL);

    std::vector<Matrix3d>::const_iterator stress_it = stresses.begin();
    for (const Tetrahedron& tet : mesh->tets) {
        const uint32_t *verts = tet.vertices();
        for (int i = 0; i < 4; i++) {
            Eigen::Vector3d norms;
            for (uint32_t normIndex : Tetrahedron::vert2normals(i)) {
                norms += tet.normals()[normIndex];
            }
            Vertex& vert = mesh->verts[verts[i]];
            vert.f += *stress_it * norms;
        }
    }
}
// --------------------------------------------------------------------------

void
step(Mesh *mesh, double dt)
{
    assert(mesh != NULL);

    std::vector<Tetrahedron>::const_iterator tet_it;
    std::vector<Matrix3d>::iterator def_it;
    std::vector<Matrix3d>::iterator strain_it;
    std::vector<Matrix3d>::iterator stress_it;

    // Clear forces
    for (Vertex& v : mesh->verts) {
        v.f = Eigen::Vector3d(0, 0, 0);
    }

    computeDeformations(mesh->tets, sDeformations);
    computeStrains(sDeformations, sStrains);
    computeStresses(sDeformations, sStrains, sStresses);
    computeForces(sStresses, mesh);

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
// --------------------------------------------------------------------------
