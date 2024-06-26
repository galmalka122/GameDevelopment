#ifndef QuadTree_h
#define QuadTree_h

#include <memory>
#include <vector>

#include "C_BoxCollider.h"
#include "Debug.h"
#include "Object.h"

class QuadTree {

public:

    QuadTree();
    QuadTree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, QuadTree* parent);

    void Insert(std::shared_ptr<C_BoxCollider> object);
    void Remove(std::shared_ptr<C_BoxCollider> object);
    void Clear();
    void DrawDebug();
    void UpdatePosition(std::shared_ptr<C_BoxCollider> object);

    std::vector<std::shared_ptr<C_BoxCollider>> Search(const sf::FloatRect& area);

private:

    [[nodiscard]] const sf::FloatRect& GetBounds() const;
    [[nodiscard]] int GetChildIndexForObject(const sf::FloatRect& objectBounds) const;

    void Split();
    void Search(const sf::FloatRect& area, std::vector<std::shared_ptr<C_BoxCollider>>& overlappingObjects);

    static const int thisTree = -1;
    static const int childNE = 0;
    static const int childNW = 1;
    static const int childSW = 2;
    static const int childSE = 3;

    int maxObjects;
    int maxLevels;

    [[maybe_unused]] QuadTree* parent;
    std::shared_ptr<QuadTree> children[4];

    // Stores all the object for this node.
    std::vector<std::shared_ptr<C_BoxCollider>> objects;

    // The distance from the root node. This will increase as we add more nodes.
    int level;

    // The bounds of this node.
    sf::FloatRect bounds;

};


#endif // QuadTree_h
