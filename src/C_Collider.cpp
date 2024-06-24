#include "C_Collider.h"

C_Collider::C_Collider(Object *owner) : Component(owner), isTrigger(false), collisionLayer(CollisionLayer::Default) { }

[[maybe_unused]] bool C_Collider::IsTrigger() const { return isTrigger; }
CollisionLayer C_Collider::GetLayer() const { return collisionLayer; }

void C_Collider::SetLayer(CollisionLayer layer) { collisionLayer = layer; }

[[maybe_unused]] void C_Collider::SetTrigger(bool isTriggered) { isTrigger = isTriggered; }
