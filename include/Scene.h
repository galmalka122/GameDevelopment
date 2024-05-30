#ifndef Scene_h
#define Scene_h

#include "Window.h"

class Scene {

public:

    // Called when the scene is initialized.
    virtual void OnCreate() = 0;

    // Called when the scene is destroyed
    virtual void OnDestroy() = 0;

    // Called when the scene is transitioned into.
    virtual void OnActivate() { };

    // Called when the scene is transitioned out.
    virtual void OnDeactivate() { };

    // These functions are optional
    virtual void ProcessInput() {};
    virtual void Update(float deltaTime) {};
    virtual void LateUpdate(float deltaTime) {};
    virtual void Draw(Window& window) {};

};


#endif //Scene_h
