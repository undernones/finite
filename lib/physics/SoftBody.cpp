#include "SoftBody.h"

using Eigen::Matrix3d;

SoftBody::SoftBody() :
    mMu(0),
    mLambda(0)
{
}

void
SoftBody::onMeshLoaded()
{
    mDeformations.resize(mMesh.tets.size());
    mStrains.resize(mMesh.tets.size());
    mStresses.resize(mMesh.tets.size());
}

void
SoftBody::setMaterial(double mu, double lambda)
{
    mMu = mu;
    mLambda = lambda;
}

void
SoftBody::clearForces()
{
    for (auto& v : mMesh.verts) {
        v.f = Eigen::Vector3d(0, 0, 0);
    }
}

void
SoftBody::computeInternalForces()
{
    computeDeformations();
    computeStrains();
    computeStresses();
    computeForces();
}

void
SoftBody::computeDeformations()
{
    auto tet_it = mMesh.tets.begin();
    auto def_it = mDeformations.begin();
    for (; def_it != mDeformations.end(); ++tet_it, ++def_it) {
        *def_it = tet_it->updateX(mMesh.verts) * tet_it->Beta();
    }
}

void
SoftBody::computeStrains()
{
    auto def_it = mDeformations.begin();
    auto strain_it = mStrains.begin();
    for (; strain_it != mStrains.end(); ++def_it, ++strain_it) {
        const Matrix3d& F = *def_it;
        // Linear Cauchy strain
        //*strain_it = 0.5 * (F + F.transpose()) - Matrix3d::Identity();
        // Quadratic Green strain
        *strain_it = 0.5 * (F.transpose() * F - Matrix3d::Identity());
    }
}

void
SoftBody::computeStresses()
{
    auto def_it = mDeformations.begin();
    auto strain_it = mStrains.begin();
    auto stress_it = mStresses.begin();
    for (; stress_it != mStresses.end(); ++strain_it, ++def_it, ++stress_it) {
        const Matrix3d& strain = *strain_it;
        const Matrix3d& F = *def_it;

        double d = lambda() * strain.trace();
        Matrix3d diag;
        diag << d, 0, 0,
                0, d, 0,
                0, 0, d;
        *stress_it = F * (2 * mu() * strain + diag);
    }
}

void
SoftBody::computeForces()
{
    auto stress_it = mStresses.begin();
    for (auto& tet : mMesh.tets) {
        auto* verts = tet.vertices();
        for (int i = 0; i < 4; i++) {
            auto& vert = mMesh.verts[verts[i]];
            vert.f += *stress_it * tet.normals()[i];
        }
        ++stress_it;
    }
}
