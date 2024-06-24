#include <cmath>
#include "C_BoxCollider.h"
#include "Object.h"

C_BoxCollider::C_BoxCollider(Object *owner) : C_Collider(owner), origin(Origin::AbsCentre), offset(sf::Vector2f(0.f, 0.f)) { }

Manifold C_BoxCollider::Intersects(std::shared_ptr<C_Collider> other)
{
    Manifold m;
    m.colliding = false;

    std::shared_ptr<C_BoxCollider> boxCollider = std::dynamic_pointer_cast<C_BoxCollider>(other);
    if(boxCollider)
    {
        const sf::FloatRect& rect1 = GetCollidable();
        const sf::FloatRect& rect2 = boxCollider->GetCollidable();

        if(rect1.intersects(rect2))
        {
            m.colliding = true;
            m.other = rect2;
        }
    }

    return m;
}

void C_BoxCollider::ResolveOverlap(const Manifold &manifold)
{
    auto transform = owner->transform;

    if(transform->IsStatic()){ return; }

    const sf::FloatRect& rect1 = GetCollidable();
    const sf::FloatRect& rect2 = manifold.other;

    if(!rect1.intersects(rect2)) { return; }

    float resolve;
    float xDiff = (rect1.left + (rect1.width * 0.5f)) - (rect2.left + (rect2.width * 0.5f));
    float yDiff = (rect1.top + (rect1.height * 0.5f)) - (rect2.top + (rect2.height * 0.5f));

    if(std::fabs(xDiff) > std::fabs(yDiff))
    {
        if(xDiff > 0)
        {
            resolve = (rect2.left + rect2.width) - rect1.left;
        }
        else
        {
            resolve = -((rect1.left + rect1.width) - rect2.left);
        }

        transform->AddPosition(resolve, 0);
    }
    else
    {
        if (yDiff > 0)
        {
            resolve = (rect2.top + rect2.height) - rect1.top;
        }
        else
        {
            resolve = -((rect1.top + rect1.height) - rect2.top);
        }

        transform->AddPosition(0, resolve);
    }
}

void C_BoxCollider::SetCollidable(const sf::FloatRect& rect)
{
    AABB = rect;
    SetPosition();
}

const sf::FloatRect &C_BoxCollider::GetCollidable()
{
    SetPosition();
    return AABB;
}

[[maybe_unused]] void C_BoxCollider::SetOrigin(const Origin &o) { origin = o; }

void C_BoxCollider::SetPosition()
{
    const sf::Vector2f& pos = owner->transform->GetPosition();

    switch(origin)
    {
        case(Origin::TopLeft):
        {
            AABB.left = pos.x + offset.x;
            AABB.top = pos.y + offset.y;
            break;
        }
        case(Origin::AbsCentre):
        {
            AABB.left = pos.x - (AABB.width / 2) + offset.x;
            AABB.top = pos.y - (AABB.height / 2) + offset.y;
            break;
        }
        case(Origin::MidBottom):
        {
            AABB.left = pos.x - (AABB.width / 2) + offset.x;
            AABB.top = pos.y - AABB.height + offset.y;
            break;
        }
    }
}

[[maybe_unused]] void C_BoxCollider::SetOffset(const sf::Vector2f &o) { offset = o; }
void C_BoxCollider::SetOffset(float x, float y) { offset.x = x; offset.y = y; }

[[maybe_unused]] void C_BoxCollider::SetSize(const sf::Vector2f &size) { AABB.width = size.x; AABB.height = size.y; }
void C_BoxCollider::SetSize(float width, float height) { AABB.width = width; AABB.height = height; }

sf::FloatRect C_BoxCollider::GetPreviewsFrameCollidable() const {
    const sf::Vector2f& pos = owner->transform->GetPreviousFramePosition();

    sf::FloatRect prevAABB;
    prevAABB.left = pos.x - (AABB.width / 2) + offset.x;
    prevAABB.top = pos.y - (AABB.height / 2) + offset.y;
    return prevAABB;
}
