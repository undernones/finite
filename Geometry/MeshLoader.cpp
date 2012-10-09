#include "MeshLoader.h"
#include <fstream>
#include "Mesh.h"
#include "Tetrahedron.h"

namespace Geometry
{

bool
MeshLoader::load(const std::string& filename, Geometry::Mesh* pMesh)
{
    VertexList verts;
    std::vector<Tetrahedron> tets;

	std::ifstream in(filename.c_str(), std::ios::in);
    if (!in.is_open()) {
        return false;
    }

	char c;
	while (in >> c) {
		if (c == 'v') {
			double x, y, z;
			in >> x >> y >> z;
			Vertex vertex;
            vertex.x = Eigen::Vector3d(x, y, z);
            vertex.u = vertex.x;
            vertex.x(2) *= 2;
            verts.push_back(vertex);
		} else if (c == 't') {
			uint32_t a, b, c, d;
			in >> a >> b >> c >> d;
            Tetrahedron tet(a, b, c, d);
            tets.push_back(tet);
		}

        if (!in) {
            in.close();
            return false;
        }
	}
	in.close();

    pMesh->init(verts, tets);
	//model.computeSurface();

	//std::vector<Tetrahedron>::iterator iter;
	//for (iter = model.m_tetrahedra.begin(); iter != model.m_tetrahedra.end(); ++iter)
	//{
	//	iter->computeVolume();
	//	iter->computeBeta();
	//	iter->computeNormals();
	//	iter->computeMasses();
	//}
    return true;
}

}
