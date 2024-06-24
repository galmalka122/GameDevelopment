#ifndef C_Animation_h
#define C_Animation_h

#include "Component.h"
#include "Animation.h"
#include "C_Sprite.h"

enum class AnimationState{

    None,
    Idle,
    Walk,

};

using AnimationList = std::map<FacingDirection, std::shared_ptr<Animation>>;

class C_Animation : public Component {

public:

    explicit C_Animation(Object* owner);

    void Awake() override;

    void Update(float deltaTime) override;
    void AddAnimation(AnimationState state, AnimationList& animationList);

    void SetAnimationState(AnimationState state);

    const AnimationState& GetAnimationState() const;
    void SetAnimationDirection(FacingDirection dir);

private:


    std::map<AnimationState, AnimationList> animations;
    std::pair<AnimationState, std::shared_ptr<Animation>> currentAnimation;
    FacingDirection currentDirection;
    std::shared_ptr<C_Sprite> sprite;

};

#endif // C_Animation_h
