#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <Eigen>

class Mesh;
class World
{
public:
    static void init(Mesh* mesh);
    static void step(double dt);

private:
    World();
    World(const World& other);
    ~World();

    World& operator=(const World& rhs);

    static Mesh* sMesh;
    static std::vector<Eigen::Matrix3d> sDeformations;
    static std::vector<Eigen::Matrix3d> sStrains;
    static std::vector<Eigen::Matrix3d> sStresses;
};

#endif // WORLD_H
