#include "S_Collidable.h"

S_Collidable::S_Collidable() : collisionTree(5, 5, 0, {0, 0, 4200, 1080}, nullptr) {

    Bitmask defaultCollision;
    defaultCollision.SetBit((int)CollisionLayer::Default);
    collisionLayers.insert(std::make_pair(CollisionLayer::Default, defaultCollision));

    collisionLayers.insert(std::make_pair(CollisionLayer::Tile, Bitmask(0)));

    Bitmask playerCollisions;
    playerCollisions.SetBit((int)CollisionLayer::Default);
    playerCollisions.SetBit((int)CollisionLayer::Tile);
    collisionLayers.insert(std::make_pair(CollisionLayer::Player, playerCollisions));

}

void S_Collidable::Add(std::vector<std::shared_ptr<Object>> &objects) {

    for(auto o : objects){

        auto collider = o->GetComponent<C_BoxCollider>();
        if(collider){

            CollisionLayer layer = collider->GetLayer();

            auto itr = collidables.find(layer);
            if(itr != collidables.end()){
                collidables[layer].push_back(collider);
            }
            else{
                std::vector<std::shared_ptr<C_BoxCollider>> objs;
                objs.push_back(collider);

                collidables.insert(std::make_pair(layer, objs));
            }
        }
    }
}

void S_Collidable::ProcessRemovals() {

    for(auto layer : collidables){
        auto itr = layer.second.begin();
        while(itr != layer.second.end()){

            if((*itr)->owner->IsQueuedForRemoval()){
                itr = layer.second.erase(itr);
            }
            else{
                ++itr;
            }
        }
    }
}

void S_Collidable::Resolve() {

    for (auto maps = collidables.begin(); maps != collidables.end(); ++maps){
        if(collisionLayers[maps->first].GetMask() == 0){
            continue;
        }

        for(auto collidable : maps->second){

            if(collidable->owner->transform->IsStatic()){ continue; }
            std::vector<std::shared_ptr<C_BoxCollider>> collisions =
                    collisionTree.Search(collidable->GetCollidable());

            for(auto collision : collisions){
                if(collidable->owner->instanceID->Get() == collision->owner->instanceID->Get()){ continue; }

                bool layersCollide = collisionLayers[collidable->GetLayer()].GetBit((int)collision->GetLayer());

                if(layersCollide){
                    Manifold m = collidable->Intersects(collision);

                    if(m.colliding){
#ifdef DEBUG
                        Debug::DrawRect(collision->GetCollidable(), sf::Color::Red);
                        Debug::DrawRect(collidable->GetCollidable(), sf::Color::Red);
#endif
                        /* if(collision->owner->transform->IsStatic()){
                            collidable->ResolveOverlap(m);
                        }
                        else{
                            collidable->ResolveOverlap(m);
                        } */
                        collidable->ResolveOverlap(m);
                    }
                }
            }
        }
    }
}

void S_Collidable::Update()
{
    collisionTree.DrawDebug();

    collisionTree.Clear();
    for(auto maps = collidables.begin(); maps != collidables.end(); ++maps){
        for(auto collidable : maps->second){
            collisionTree.Insert(collidable);
        }
    }

    Resolve();
}