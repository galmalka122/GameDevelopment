#include "QuadTree.h"

QuadTree::QuadTree() : QuadTree(5, 5, 0, {0.f, 0.f, 1920, 1080}, nullptr) { }

QuadTree::QuadTree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, QuadTree *parent) :
    maxObjects(maxObjects), maxLevels(maxLevels), level(level), bounds(bounds), parent(parent) { }

void QuadTree::Insert(std::shared_ptr<C_BoxCollider> object) {

    if(children[0] != nullptr){

        int indexToPlaceObject = GetChildIndexForObject(object->GetCollidable());

        if(indexToPlaceObject != thisTree){

            children[indexToPlaceObject]->Insert(object);
            return;
        }
    }

    objects.emplace_back(object);

    if(objects.size() > maxObjects && level < maxLevels && children[0] == nullptr){

        Split();

        auto it = objects.begin();
        while (it != objects.end()){

            auto obj = *object;
            int indexToPlaceObject = GetChildIndexForObject(object->GetCollidable());

            if(indexToPlaceObject != thisTree){

                children[indexToPlaceObject]->Insert(object);
                it = objects.erase(it);
            }

            else ++it;
        }
    }
}

void QuadTree::Remove(std::shared_ptr<C_BoxCollider> object) {

    int index = GetChildIndexForObject(object->GetCollidable());

    if(index == thisTree || children[index] == nullptr){

        for (int i = 0; i < objects.size(); ++i) {

            if(objects.at(i)->owner->instanceID->Get() == object->owner->instanceID->Get()){

                objects.erase(objects.begin() + i);
                break;
            }
        }
    }

    else return children[index]->Remove(object);
}

void QuadTree::Clear() {

    objects.clear();

    for (int i = 0; i < 4; ++i) {
        if(children[i] != nullptr){

            children[i]->Clear();
            children[i] = nullptr;

        }
    }

}