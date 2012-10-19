#include "MeshLoader.h"
#include <fstream>
#include "Mesh.h"
#include "Tetrahedron.h"

bool
MeshLoader::load(const std::string& filename, Mesh* pMesh, double density)
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
            //vertex.x(2) *= 0.01;
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

    pMesh->init(verts, tets, density);
    return true;
}
