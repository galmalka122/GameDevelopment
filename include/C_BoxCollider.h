#ifndef C_BoxCollider_h
#define C_BoxCollider_h

#include "Component.h"
#include "C_Collider.h"

enum class Origin { TopLeft, AbsCentre, MidBottom };

class C_BoxCollider : public C_Collider {

public:

    explicit C_BoxCollider(Object* owner);
    ~C_BoxCollider() = default;

    Manifold Intersects(std::shared_ptr<C_Collider> other) override;
    void ResolveOverlap(const Manifold &manifold) override;

    void SetCollidable(const sf::FloatRect& rect);
    const sf::FloatRect& GetCollidable();
    sf::FloatRect GetPreviewsFrameCollidable() const;

    [[maybe_unused]] void SetOrigin(const Origin& o);
    [[maybe_unused]] void SetOffset(const sf::Vector2f& offset);
    void SetOffset(float x, float y);

    [[maybe_unused]] void SetSize(const sf::Vector2f& size);
    void SetSize(float width, float height);

private:

    void SetPosition();

    sf::FloatRect AABB;
    Origin origin;
    sf::Vector2f offset;


};


#endif // C_BoxCollider_h
