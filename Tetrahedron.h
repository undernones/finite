#ifndef GEOMETRY_TETRAHEDRON_H
#define GEOMETRY_TETRAHEDRON_H

#include <Eigen>
#include "Vertex.h"

class Tetrahedron
{
public:
    Tetrahedron(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
    Tetrahedron(const Tetrahedron& other);
    ~Tetrahedron();

    Tetrahedron& operator =(const Tetrahedron& rhs);

    void init(VertexList& verts, double density);

    double volume() const { return mVolume; }
    const Eigen::Matrix3d& updateX(const VertexList& verts);
    const Eigen::Matrix3d& X() const { return mX; }
    const Eigen::Matrix3d& updateBeta(const VertexList& verts);
    const Eigen::Matrix3d& Beta() const { return mBeta; }

    const uint32_t* vertices() const { return mVix; }
    const Eigen::Vector3d* normals() const { return mNormals; }

    static const std::vector<uint32_t>& vert2normals(uint32_t index);

private:
    uint32_t mVix[4]; // vertex indices
    Eigen::Matrix3d mBasis;
    Eigen::Matrix3d mBeta;
    Eigen::Matrix3d mX;
    Eigen::Vector3d mNormals[4];
    double mVolume;

    void computeVolume();
    void computeNormals();
    void computeMasses(VertexList& verts, double density);
};

#endif // GEOMETRY_TETRAHEDRON_H
