#include "Object.h"

using shared_component = std::shared_ptr<Component>;

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

void Object::Draw(Window &window) {

    for(const shared_component& component : components){
        component->Draw(window);
    }
}
