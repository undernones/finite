#include "Vertex.h"

Vertex::Vertex()
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
