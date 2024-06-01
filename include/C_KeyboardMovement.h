#ifndef C_KeyboardMovement_h
#define C_KeyboardMovement_h

#include "Component.h"
#include "Input.h"
#include "C_Animation.h"

class C_KeyboardMovement : public Component {

public:

    explicit C_KeyboardMovement(Object* owner);

    void SetInput(Input* input);
    void SetMovementSpeed(float moveSpeed);

    void Update(float deltaTime) override;

    void Awake() override;

private:

    float moveSpeed;
    Input* input;

    std::shared_ptr<C_Animation> animation;

};


#endif // C_KeyboardMovement_h
