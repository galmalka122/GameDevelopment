#include "Object.h"

using shared_component = std::shared_ptr<Component>;

Object::Object() : queuedForRemoval(false) {
    transform = AddComponent<C_Transform>();
    instanceID = AddComponent<C_InstanceID>();
}

void Object::QueueForRemoval() { queuedForRemoval = true; }
bool Object::IsQueuedForRemoval() { return queuedForRemoval; }
std::shared_ptr<C_Drawable> Object::GetDrawable() { return drawable; }
void Object::Draw(Window &window) { drawable->Draw(window); }

void Object::Awake() {

    for(const shared_component& component : components){
        component->Awake();
    }
}

void Object::Start() {

    for(const shared_component& component : components){
        component->Start();
    }
}

void Object::Update(float deltaTime) {

    for(const shared_component& component : components){
        component->Update(deltaTime);
    }
}

void Object::LateUpdate(float deltaTime) {

    for(const shared_component& component : components){
        component->LateUpdate(deltaTime);
    }
}




