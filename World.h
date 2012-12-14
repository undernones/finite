#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include <Eigen>
#include <geom/Mesh.h>
#include <physics/SoftBody.h>

class Obstacle;
class World
{
public:
    static void init(const std::string& filename);
    static void step(double dt);
    static const SoftBody& softBody() { return sBody; }

private:
    World();
    World(const World& other);
    ~World();

    World& operator=(const World& rhs);

    static SoftBody sBody;
    static std::vector<Obstacle*> sObstacles;
};

#endif // WORLD_H
