#ifndef C_Camera_h
#define C_Camera_h

#include "Component.h"


class C_Camera : public Component {

public:

    C_Camera(Object* owner);

    void LateUpdate(float deltaTime) override;

    void SetWindow(Window* gameWindow);

private:

    Window* window;

};


#endif // C_Camera_h
