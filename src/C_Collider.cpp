#include "C_Collider.h"

C_Collider::C_Collider(Object *owner) : Component(owner), collisionLayer(CollisionLayer::Default) { }
C_Collider::~C_Collider() { }

bool C_Collider::IsTrigger() const { return isTrigger; }
CollisionLayer C_Collider::GetLayer() const { return collisionLayer; }

void C_Collider::SetCollisionLayer(CollisionLayer layer) { collisionLayer = layer; }
void C_Collider::SetTrigger(bool isTriggered) { isTrigger = isTriggered; }
