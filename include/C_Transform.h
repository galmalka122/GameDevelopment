#ifndef C_Transform_h
#define C_Transform_h

#include "Component.h"

class C_Transform : public Component {

public:

    explicit C_Transform(Object* owner);

    void AddPosition(float x, float y);
    void AddPosition(const sf::Vector2f& pos);

    void SetPosition(float x, float y);
    void SetPosition(const sf::Vector2f& pos);

    void SetX(float x);
    void SetY(float y);

    void SetStatic(bool isStatic);
    bool IsStatic() const;

    [[nodiscard]] const sf::Vector2f& GetPosition() const;
    const sf::Vector2f& GetPreviousFramePosition() const { return previewsFramePosition; }

    void LateUpdate(float deltaTime) override;;

private:

    sf::Vector2f position;
    sf::Vector2f previewsFramePosition;
    bool isStatic;

};


#endif // C_Transform_h
