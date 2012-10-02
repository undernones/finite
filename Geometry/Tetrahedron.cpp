#include "Tetrahedron.h"

namespace
{

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

Tetrahedron::Tetrahedron() :
    X(),
    Beta(),
    u(), v(), w()
{
    verts[0] = 0;
    verts[1] = 0;
    verts[2] = 0;
    verts[3] = 0;
}

Tetrahedron::Tetrahedron(uint32_t a, uint32_t b, uint32_t c, uint32_t d) :
    X(),
    Beta(),
    u(), v(), w()
{
    verts[0] = a;
    verts[1] = b;
    verts[2] = c;
    verts[3] = d;
}

Tetrahedron::Tetrahedron(const Tetrahedron& other) :
    X(other.X),
    Beta(other.Beta),
    u(other.u),
    v(other.v),
    w(other.w)
{
    memcpy(verts, other.verts, sizeof(verts[0]) * 4);
}

Tetrahedron::~Tetrahedron()
{}

Tetrahedron&
Tetrahedron::operator =(const Tetrahedron& rhs)
{
    if (this != &rhs) {
        X = rhs.X;
        Beta = rhs.Beta;
        u = rhs.u;
        v = rhs.v;
        w = rhs.w;
        memcpy(verts, rhs.verts, sizeof(verts[0]) * 4);
    }
    return *this;
}

void
Tetrahedron::init(const std::vector<Vertex>& vertices)
{
    u = vertices[verts[1]].u - vertices[verts[0]].u;
    v = vertices[verts[2]].u - vertices[verts[0]].u;
    w = vertices[verts[3]].u - vertices[verts[0]].u;
    setCol(&X, 0, u);
    setCol(&X, 1, v);
    setCol(&X, 2, w);

    Eigen::Vector3d U = vertices[verts[1]].x - vertices[verts[0]].x;
    Eigen::Vector3d V = vertices[verts[2]].x - vertices[verts[0]].x;
    Eigen::Vector3d W = vertices[verts[3]].x - vertices[verts[0]].x;
    setCol(&Beta, 0, U);
    setCol(&Beta, 1, V);
    setCol(&Beta, 2, W);
    Beta = Beta.inverse().eval();
	//	iter->computeVolume();
	//	iter->computeNormals();
	//	iter->computeMasses();
}

}
