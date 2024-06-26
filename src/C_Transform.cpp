#include "C_Transform.h"

C_Transform::C_Transform(Object *owner) : Component(owner), position(0.f, 0.f), isStatic(false), previewsFramePosition(0.f, 0.f) { }

void C_Transform::LateUpdate(float deltaTime) { previewsFramePosition = position; }

void C_Transform::SetX(float x) { position.x = x; }
void C_Transform::SetY(float y) { position.y = y; }

void C_Transform::SetStatic(bool isStatic) { this->isStatic = isStatic; }
bool C_Transform::IsStatic() const { return isStatic; }

void C_Transform::AddPosition(const sf::Vector2f& pos) { position += pos; }
void C_Transform::SetPosition(const sf::Vector2f& pos) { position = pos; }
const sf::Vector2f &C_Transform::GetPosition() const { return position; }

void C_Transform::SetPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

void C_Transform::AddPosition(float x, float y) {
    position.x += x;
    position.y += y;
}

