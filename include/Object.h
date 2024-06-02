#ifndef Object_h
#define Object_h

#include <vector>
#include <memory>

#include "Window.h"
#include "Component.h"
#include "C_Transform.h"
#include "C_Drawable.h"

class Object{

public:

    Object() : queuedForRemoval(false) { transform = AddComponent<C_Transform>(); }

    // Called when the object is created.
    void Awake();

    // Called after Awake. This is where we initialize variables.
    void Start();

    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw(Window& window);

    bool IsQueuedForRemoval();
    void QueueForRemoval();

    template<class T> std::shared_ptr<T> AddComponent(){

        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        for (auto& existingComponent : components) {

            if(std::dynamic_pointer_cast<T>(existingComponent)){
                return std::dynamic_pointer_cast<T>(existingComponent);
            }

        }

        std::shared_ptr<T> newComponent = std::make_shared<T>(this);
        components.push_back(newComponent);

        if(std::dynamic_pointer_cast<C_Drawable>(newComponent)){
            drawable = std::dynamic_pointer_cast<C_Drawable>(newComponent);
        }

        return newComponent;

    }

    template<class T> std::shared_ptr<T> GetComponent(){

        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        for(auto existingComponent: components){
            if(std::dynamic_pointer_cast<T>(existingComponent)){ return std::dynamic_pointer_cast<T>(existingComponent); }
        }

        return nullptr;

    }

    std::shared_ptr<C_Drawable> GetDrawable();

    std::shared_ptr<C_Transform> transform;

private:

    std::vector<std::shared_ptr<Component>> components;
    std::shared_ptr<C_Drawable> drawable;

    bool queuedForRemoval;

};

#endif // Object_h
