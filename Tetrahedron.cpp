#include "Tetrahedron.h"

namespace
{

const double ONE_6TH = 1.0 / 6.0;

void
setCol(Eigen::Matrix3d* m, uint32_t col, const Eigen::Vector3d& v)
{
    assert(m != NULL);
    (*m)(0, col) = v(0);
    (*m)(1, col) = v(1);
    (*m)(2, col) = v(2);
}

Eigen::Vector3d
getCol(const Eigen::Matrix3d& m, uint32_t col)
{
    return Eigen::Vector3d(
        m(0, col),
        m(1, col),
        m(2, col)
    );
}

} // end unnamed namespace


Tetrahedron::Tetrahedron(uint32_t index, uint32_t a, uint32_t b, uint32_t c, uint32_t d) :
    mIndex(index),
    mBasis(),
    mBeta(),
    mX(),
    mVolume(0)
{
    mVix[0] = a;
    mVix[1] = b;
    mVix[2] = c;
    mVix[3] = d;
}

Tetrahedron::Tetrahedron(const Tetrahedron& other) :
    mIndex(other.mIndex),
    mBasis(other.mBasis),
    mBeta(other.mBeta),
    mX(other.mX),
    mVolume(other.mVolume)
{
    for (int i = 0; i < 4; ++i) {
        mVix[i] = other.mVix[i];
        mNormals[i] = other.mNormals[i];
    }
}

Tetrahedron::~Tetrahedron()
{}

Tetrahedron&
Tetrahedron::operator =(const Tetrahedron& rhs)
{
    if (this != &rhs) {
        mIndex = rhs.mIndex;
        mBasis = rhs.mBasis;
        mBeta = rhs.mBeta;
        mX = rhs.mX;
        mVolume = rhs.mVolume;
        for (int i = 0; i < 4; ++i) {
            mVix[i] = rhs.mVix[i];
            mNormals[i] = rhs.mNormals[i];
        }
    }
    return *this;
}

void
Tetrahedron::init(VertexList& verts, double density)
{
    updateX(verts);
    updateBeta(verts);
    computeVolume();
    computeNormals();
    computeMasses(verts, density);
}

const Eigen::Matrix3d&
Tetrahedron::updateX(const VertexList& verts)
{
    Eigen::Vector3d u = verts[mVix[1]].x - verts[mVix[0]].x;
    Eigen::Vector3d v = verts[mVix[2]].x - verts[mVix[0]].x;
    Eigen::Vector3d w = verts[mVix[3]].x - verts[mVix[0]].x;
    setCol(&mX, 0, u);
    setCol(&mX, 1, v);
    setCol(&mX, 2, w);
    return mX;
}

const Eigen::Matrix3d&
Tetrahedron::updateBeta(const VertexList& verts)
{
    Eigen::Vector3d u = verts[mVix[1]].u - verts[mVix[0]].u;
    Eigen::Vector3d v = verts[mVix[2]].u - verts[mVix[0]].u;
    Eigen::Vector3d w = verts[mVix[3]].u - verts[mVix[0]].u;
    setCol(&mBasis, 0, u);
    setCol(&mBasis, 1, v);
    setCol(&mBasis, 2, w);
    mBeta = mBasis.inverse().eval();
    return mBeta;
}

const std::vector<uint32_t>&
Tetrahedron::vert2normals(uint32_t index)
{
    static std::vector<uint32_t> v[4];
    static bool firstTime = true;
    if (firstTime) {
        firstTime = false;

        v[0].reserve(3);
        v[0].push_back(1);
        v[0].push_back(2);
        v[0].push_back(3);

        v[1].reserve(3);
        v[1].push_back(0);
        v[1].push_back(2);
        v[1].push_back(3);

        v[2].reserve(3);
        v[2].push_back(0);
        v[2].push_back(1);
        v[2].push_back(3);

        v[3].reserve(3);
        v[3].push_back(0);
        v[3].push_back(1);
        v[3].push_back(2);
    }
    return v[index];
}

void
Tetrahedron::computeVolume()
{
    mVolume = ONE_6TH * mBasis.determinant();
}

void
Tetrahedron::computeNormals()
{
    Eigen::Vector3d cols[] = {
        getCol(mBasis, 0),
        getCol(mBasis, 1),
        getCol(mBasis, 2),
    };
    mNormals[1] = ONE_6TH * cols[2].cross(cols[1]);
    mNormals[2] = ONE_6TH * cols[0].cross(cols[2]);
    mNormals[3] = ONE_6TH * cols[1].cross(cols[0]);
    mNormals[0] = -mNormals[1] - mNormals[2] - mNormals[3];
}

void
Tetrahedron::computeMasses(VertexList& verts, double density)
{
    double mass_4 = 0.25 * mVolume * density;
    verts[mVix[0]].mass += mass_4;
    verts[mVix[1]].mass += mass_4;
    verts[mVix[2]].mass += mass_4;
    verts[mVix[3]].mass += mass_4;
}
