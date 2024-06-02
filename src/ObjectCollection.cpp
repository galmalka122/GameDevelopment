#include "ObjectCollection.h"

void ObjectCollection::Add(std::shared_ptr<Object> object) { newObjects.push_back(object); }
void ObjectCollection::Draw(Window &window) { drawables.Draw(window); }

void ObjectCollection::Update(float deltaTime) {
    for(auto& object : objects) { object->Update(deltaTime); }
}

void ObjectCollection::LateUpdate(float deltaTime) {
    for(auto& object : objects) { object->LateUpdate(deltaTime); }
}

void ObjectCollection::ProcessNewObjects() {

    if(newObjects.size() > 0){

        // Awake all objects and then start.
        for(const auto& object : newObjects) { object->Awake(); }
        for(const auto& object : newObjects) { object->Start(); }

        objects.insert(objects.end(), newObjects.begin(), newObjects.end());
        drawables.Add(newObjects);
        newObjects.clear();
    }

}

void ObjectCollection::ProcessRemovals() {

    auto it = objects.begin();
    while(it != objects.end()){

        auto obj = **it;

        if(obj.IsQueuedForRemoval()) { it = objects.erase(it); }
        else { ++it; }

    }

    drawables.ProcessRemovals();
}

void ObjectCollection::Add(std::vector<std::shared_ptr<Object>> objects) {
    newObjects.insert(newObjects.end(), objects.begin(), objects.end());
}
