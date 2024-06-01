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

class C_Animation : public Component {

public:

    explicit C_Animation(Object* owner);

    void Awake() override;

    void Update(float deltaTime) override;
    void AddAnimation(AnimationState state, std::shared_ptr<Animation> animation);

    void SetAnimationState(AnimationState state);

    const AnimationState& GetAnimationState() const;
    void SetAnimationDirection(FacingDirection dir);

private:

    std::shared_ptr<C_Sprite> sprite;
    std::map<AnimationState, std::shared_ptr<Animation>> animations;

    std::pair<AnimationState, std::shared_ptr<Animation>> currentAnimation;

};

#endif // C_Animation_h
