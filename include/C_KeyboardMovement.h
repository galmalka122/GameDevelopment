#ifndef C_KeyboardMovement_h
#define C_KeyboardMovement_h

#include "Component.h"
#include "Input.h"

class C_KeyboardMovement : public Component {

public:

    explicit C_KeyboardMovement(Object* owner);

    void SetInput(Input* input);
    void SetMovementSpeed(float moveSpeed);

    void Update(float deltaTime) override;

private:

    float moveSpeed;
    Input* input;

};


#endif // C_KeyboardMovement_h
