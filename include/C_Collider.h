#ifndef C_Collider_h
#define C_Collider_h

#include <memory>
#include <SFML/Graphics.hpp>

#include "Component.h"

enum class CollisionLayer{

    Default = 1,
    Player = 2,
    Tile = 3

};

struct Manifold{

    bool colliding = false;
    const sf::FloatRect* other;

};

class C_Collider : public Component{

public:

    C_Collider(Object* owner);
    ~C_Collider();

    virtual Manifold Intersects(std::shared_ptr<C_Collider> other) = 0;
    virtual void ResolveOverlap(const Manifold& manifold) = 0;

    bool IsTrigger() const;
    void SetTrigger(bool isTriggered);

    CollisionLayer GetLayer() const;
    void SetCollisionLayer(CollisionLayer layer);

private:

    bool isTrigger;
    CollisionLayer collisionLayer;

};


#endif // C_Collider_h
