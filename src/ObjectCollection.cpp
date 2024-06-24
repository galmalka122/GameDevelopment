#include "ObjectCollection.h"

void ObjectCollection::Add(std::shared_ptr<Object> &object) { newObjects.push_back(object); }

void ObjectCollection::Add(std::vector<std::shared_ptr<Object>>& o) {
    newObjects.insert(newObjects.end(), o.begin(), o.end());
}

void ObjectCollection::Draw(Window &window) { drawables.Draw(window); }

void ObjectCollection::Update(float deltaTime) {
    for(const auto& object : objects) { object->Update(deltaTime); }

    collidables.Update();
}

void ObjectCollection::LateUpdate(float deltaTime) {
    for(const auto& object : objects) { object->LateUpdate(deltaTime); }
}

void ObjectCollection::ProcessNewObjects() {

    if(!newObjects.empty()){

        // Awake all objects and then start.
        for(const auto& object : newObjects) { object->Awake(); }
        for(const auto& object : newObjects) { object->Start(); }

        objects.insert(objects.end(), newObjects.begin(), newObjects.end());
        drawables.Add(newObjects);
        collidables.Add(newObjects);
        newObjects.clear();
    }


}

void ObjectCollection::ProcessRemovals() {

    bool removed = false;
    auto objIterator = objects.begin();

    while(objIterator != objects.end()){
        auto obj = *objIterator;

        if(obj->IsQueuedForRemoval()) {
            objIterator = objects.erase(objIterator);
            removed = true;
        }
        else { ++objIterator; }

    }
    if(removed) {
        drawables.ProcessRemovals();
        collidables.ProcessRemovals();
    }
}

