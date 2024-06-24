#include "C_Animation.h"
#include "Object.h"

C_Animation::C_Animation(Object *owner) : Component(owner), currentAnimation(AnimationState::None, nullptr), currentDirection(FacingDirection::Down) { }

void C_Animation::Awake() { sprite = owner->GetComponent<C_Sprite>(); }
const AnimationState &C_Animation::GetAnimationState() const { return currentAnimation.first; }

void C_Animation::Update(float deltaTime)
{
    // Check if animation is playing.
    if(currentAnimation.first != AnimationState::None)
    {
        bool newFrame = currentAnimation.second->UpdateFrame(deltaTime);
        if(newFrame)
        {
            const FrameData* data = currentAnimation.second->GetCurrentFrame();

            sprite->Load(data->id);
            sprite->SetTextureRect(data->x, data->y, data->width, data->height);
        }
    }
}

void C_Animation::AddAnimation(AnimationState state, AnimationList& animationList) {

    auto inserted = animations.insert(std::make_pair(state, animationList));

    if(currentAnimation.first == AnimationState::None) { SetAnimationState(state); }

}

void C_Animation::SetAnimationState(AnimationState state) {

    // We don't need to change the state.
    if(currentAnimation.first == state) { return; }

    // Check if we have animation for the current state.
    auto animationList = animations.find(state);
    if(animationList != animations.end())
    {
        // Check if we have animation for the current direction.
        auto animation = animationList->second.find(currentDirection);
        if(animation != animationList->second.end())
        {
            // Switch the state and the animation.
            currentAnimation.first = animationList->first;
            currentAnimation.second = animation->second;
            currentAnimation.second->Reset();
        }
    }
}

void C_Animation::SetAnimationDirection(FacingDirection dir)
{
    if(dir != currentDirection)
    {
        currentDirection = dir;

        // Check if we have animation for the current state.
        auto animationList = animations.find(currentAnimation.first);
        if(animationList != animations.end())
        {
            // Check if we have animation for the current direction.
            auto animation = animationList->second.find(dir);
            if(animation != animationList->second.end())
            {
                // Switch animation.
                currentAnimation.second = animation->second;
                currentAnimation.second->Reset();
            }
        }
    }
}


