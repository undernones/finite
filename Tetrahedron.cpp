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

} // end unnamed namespace


Tetrahedron::Tetrahedron(uint32_t a, uint32_t b, uint32_t c, uint32_t d) :
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
Tetrahedron::init(const VertexList& verts)
{
    updateX(verts);
    updateBeta(verts);
    computeVolume();

	//	iter->computeNormals();
	//	iter->computeMasses();
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

void
Tetrahedron::computeVolume()
{
    mVolume = ONE_6TH * mBasis.determinant();
}

