#ifndef ObjectCollection_h
#define ObjectCollection_h

#include <memory>
#include <vector>

#include "Object.h"
#include "S_Drawable.h"
#include "S_Collidable.h"

class ObjectCollection {

public:

    void Add(std::shared_ptr<Object> &object);
    void Add(std::vector<std::shared_ptr<Object>>& objects);

    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw(Window& window);

    void ProcessNewObjects();
    void ProcessRemovals();

private:

    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Object>> newObjects;
    S_Drawable drawables;
    S_Collidable collidables;
};


#endif // ObjectCollection_h
