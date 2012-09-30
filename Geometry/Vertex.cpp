#include "Vertex.h"

namespace Geometry
{

Vertex::Vertex() :
    x(0, 0, 0),
    v(0, 0, 0),
    f(0, 0, 0),
    mass(0)
{
}

Vertex::Vertex(const Vertex& other) :
    x(other.x),
    v(other.v),
    f(other.f),
    mass(other.mass)
{
}

Vertex& Vertex::operator =(const Vertex& rhs)
{
    return *this;
}

}
