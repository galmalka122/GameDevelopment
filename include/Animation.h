#ifndef Animation_h
#define Animation_h

#include <functional>
#include <map>
#include <vector>

#include "Bitmask.h"

struct FrameData {

    // Texture's id
    int id;

    // Texture's position
    int x; // x position
    int y; // y

    // Texture's bounds
    int width;
    int height;

    // Time to display
    float displayTimeSeconds;

};

enum class FacingDirection{

    None,
    Left,
    Right,
    Up,
    Down

};

using AnimationAction = std::function<void(void)>;

class Animation {

public:

    Animation();

    void AddFrame(int textureID, int x, int y, int width, int height, float displayTimeSeconds);

    void AddFrameAction(unsigned int frame, AnimationAction action);

    [[nodiscard]] const FrameData* GetCurrentFrame() const;

    bool UpdateFrame(float deltaTime);

    void Reset();

private:

    void IncrementFrame();
    void RunActionForCurrentFrame();

    // Stores all the animation's frames.
    std::vector<FrameData> frames;

    std::map<int, std::vector<AnimationAction>> actions;

    Bitmask framesWithActions;

    int currentFrameIndex;

    // This is to help determine when to switch to the next frame.
    float currentFrameTime;

    bool releaseFirstFrame;

};


#endif // Animation_h
