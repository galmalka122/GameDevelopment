#ifndef Component_h
#define Component_h

#include "Window.h"

class Object;

class Component{

public:

    Component(Object* owner) : owner(owner) { };

    virtual void Awake() { };
    virtual void Start() { };

    virtual void Update(float deltaTime) { };
    virtual void LateUpdate(float deltaTime) { };
    virtual void Draw(Window& window) { };

    Object* owner;

protected:



};

#endif // Component_h
