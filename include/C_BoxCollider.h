#ifndef C_BoxCollider_h
#define C_BoxCollider_h

#include "Component.h"
#include "C_Collider.h"


class C_BoxCollider : public C_Collider {

public:

    C_BoxCollider(Object* owner);

    Manifold Intersects(std::shared_ptr<C_Collider> other) override;
    void ResolveOverlap(const Manifold &manifold) override;

    void setCollidable(const sf::FloatRect& rect);
    const sf::FloatRect& GetCollidable();

private:

    void SetPosition();

    sf::FloatRect AABB;
    sf::Vector2f offset;

};


#endif // C_BoxCollider_h
