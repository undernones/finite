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

}

namespace Geometry
{

Tetrahedron::Tetrahedron(uint32_t a, uint32_t b, uint32_t c, uint32_t d) :
    u(), v(), w(),
    mX(),
    mBeta()
{
    this->verts[0] = a;
    this->verts[1] = b;
    this->verts[2] = c;
    this->verts[3] = d;
}

Tetrahedron::Tetrahedron(const Tetrahedron& other) :
    u(other.u),
    v(other.v),
    w(other.w),
    mX(other.mX),
    mBeta(other.mBeta)
{
    memcpy(verts, other.verts, sizeof(verts[0]) * 4);
}

Tetrahedron::~Tetrahedron()
{}

Tetrahedron&
Tetrahedron::operator =(const Tetrahedron& rhs)
{
    if (this != &rhs) {
        mX = rhs.mX;
        mBeta = rhs.mBeta;
        u = rhs.u;
        v = rhs.v;
        w = rhs.w;
        memcpy(verts, rhs.verts, sizeof(verts[0]) * 4);
    }
    return *this;
}

void
Tetrahedron::init(const VertexList& vertices)
{
    updateX(vertices);
    updateBeta(vertices);
    computeVolume();

	//	iter->computeNormals();
	//	iter->computeMasses();
}

const Eigen::Matrix3d&
Tetrahedron::updateX(const VertexList& vertices)
{
    Eigen::Vector3d U = vertices[verts[1]].x - vertices[verts[0]].x;
    Eigen::Vector3d V = vertices[verts[2]].x - vertices[verts[0]].x;
    Eigen::Vector3d W = vertices[verts[3]].x - vertices[verts[0]].x;
    setCol(&mX, 0, U);
    setCol(&mX, 1, V);
    setCol(&mX, 2, W);
    return mX;
}

const Eigen::Matrix3d&
Tetrahedron::updateBeta(const VertexList& vertices)
{
    u = vertices[verts[1]].u - vertices[verts[0]].u;
    v = vertices[verts[2]].u - vertices[verts[0]].u;
    w = vertices[verts[3]].u - vertices[verts[0]].u;
    setCol(&mBeta, 0, u);
    setCol(&mBeta, 1, v);
    setCol(&mBeta, 2, w);
    mBeta = mBeta.inverse().eval();
    return mBeta;
}

void
Tetrahedron::computeVolume()
{
    mVolume = u.cross(v).dot(w) * ONE_6TH;
}

}
