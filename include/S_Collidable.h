#ifndef S_Collidable_h
#define S_Collidable_h

#include <vector>
#include <memory>
#include <set>

#include "Object.h"
#include "QuadTree.h"
#include "Bitmask.h"

class S_Collidable {

public:

    S_Collidable();

    void Add(std::vector<std::shared_ptr<Object>>& objects);
    void ProcessRemovals();
    void Update();

private:

    void Resolve();

    [[maybe_unused]] static void ProcessCollisions(std::vector<std::shared_ptr<Object>>& first, std::vector<std::shared_ptr<Object>>& second) { first; second; };

    std::map<CollisionLayer, Bitmask> collisionLayers;
    std::map<CollisionLayer, std::vector<std::shared_ptr<C_BoxCollider>>> collidables;

    QuadTree collisionTree;

};

#endif // S_Collidable_h
