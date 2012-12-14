#ifndef PHYSICS_SOFTBODY_H
#define PHYSICS_SOFTBODY_H

#include <vector>
#include <Eigen>
#include <geom/Mesh.h>

class SoftBody
{
public:
    SoftBody();
    ~SoftBody() {}

    void onMeshLoaded();
    void setMaterial(double mu, double lambda);

    Mesh& mesh() { return mMesh; }
    const Mesh& mesh() const { return mMesh; }

    const std::vector<Eigen::Matrix3d> deformations() const { return mDeformations; }
    const std::vector<Eigen::Matrix3d> strains() const { return mStrains; }
    const std::vector<Eigen::Matrix3d> stresses() const { return mStresses; }

    inline double mu() const { return mMu; }
    inline double lambda() const { return mLambda; }

    void clearForces();
    void computeInternalForces();

private:
    Mesh mMesh;
    std::vector<Eigen::Matrix3d> mDeformations;
    std::vector<Eigen::Matrix3d> mStrains;
    std::vector<Eigen::Matrix3d> mStresses;
    double mMu;
    double mLambda;

    SoftBody(const SoftBody&);
    SoftBody& operator =(const SoftBody&);

    void computeDeformations();
    void computeStrains();
    void computeStresses();
    void computeForces();
};

#endif // PHYSICS_SOFTBODY_H
