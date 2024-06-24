#include "C_KeyboardMovement.h"
#include "Object.h"

C_KeyboardMovement::C_KeyboardMovement(Object *owner) : Component(owner), moveSpeed(200.f) { }
void C_KeyboardMovement::SetInput(Input *input) { this->input = input; }
void C_KeyboardMovement::SetMovementSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }
void C_KeyboardMovement::Awake() { animation = owner->GetComponent<C_Animation>(); }

void C_KeyboardMovement::Update(float deltaTime)
{
    if(input == nullptr) { return; }

    float xMove = 0.f;

    if(input->IsKeyPressed(Input::Key::Left)){ xMove = -moveSpeed; }
    else if(input->IsKeyPressed(Input::Key::Right)){ xMove = moveSpeed; }

    float yMove = 0.f;

    if(input->IsKeyPressed(Input::Key::Up)){ yMove = -moveSpeed; }
    else if(input->IsKeyPressed(Input::Key::Down)) { yMove = moveSpeed; }

    float xFrameMove = xMove * deltaTime;
    float yFrameMove = yMove * deltaTime;

    owner->transform->AddPosition(xFrameMove, yFrameMove);

    if(xMove == 0 && yMove == 0){ animation->SetAnimationState(AnimationState::Idle); }

    else
    {
        animation->SetAnimationState(AnimationState::Walk);

        if(std::abs(xMove) > std::abs(yMove))
        {
            if(xMove < 0) { animation->SetAnimationDirection(FacingDirection::Left); }
            else { animation->SetAnimationDirection(FacingDirection::Right); }
        }
        else
        {
            if(yMove < 0) { animation->SetAnimationDirection(FacingDirection::Up); }
            else { animation->SetAnimationDirection(FacingDirection::Down); }
        }
    }
}


