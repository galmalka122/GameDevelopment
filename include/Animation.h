#ifndef Animation_h
#define Animation_h

#include <vector>

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

};

class Animation {

public:

    Animation(FacingDirection direction);

    void AddFrame(int textureID, int x, int y, int width, int height, float displayTimeSeconds);
    void SetDirection(FacingDirection direction);

    const FrameData* GetCurrentFrame() const;
    FacingDirection GetDirection() const;

    bool UpdateFrame(float deltaTime);

    void Reset();

private:

    void IncrementFrame();

    // Stores all the animation's frames.
    std::vector<FrameData> frames;

    int currentFrameIndex;

    // This is to help determine when to switch to the next frame.
    float currentFrameTime;

    FacingDirection direction;

};


#endif // Animation_h
