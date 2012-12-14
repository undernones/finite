#include "World.h"
#include <iostream>
#include <geom/MeshLoader.h>
#include <physics/PlaneObstacle.h>
#include "Options.h"

SoftBody World::sBody;
std::vector<Obstacle*> World::sObstacles;

void
World::init(const std::string& filename)
{
    if (!MeshLoader::load(filename, &sBody.mesh(), Options::density())) {
        throw std::exception();
    }
    sBody.onMeshLoaded();
    sBody.setMaterial(Options::mu(), Options::lambda());

    sObstacles.push_back(new PlaneObstacle(Eigen::Vector3d(0, 1, 0), -2, Options::friction()));
    //sObstacles.push_back(new PlaneObstacle(Eigen::Vector3d(0, -1, 0), -1, Options::friction()));
}

void
World::step(double dt)
{
    // Clear forces
    sBody.clearForces();
    sBody.computeInternalForces();

    // Integrate
    for (auto& v : sBody.mesh().verts) {
        static Eigen::Vector3d g(0, Options::gravity(), 0);
        auto a = v.f / v.mass + g;
        v.v += dt * a * 0.99;
        v.x += dt * v.v;
    }

    // Collide
    for (auto o : sObstacles) {
        for (auto& vert : sBody.mesh().verts) {
            if (o->bounce(vert)) {
                //std::cout << "hit!" << std::endl;
            }
        }
    }
}

