#include <cstdint>
#include "Animation.h"

Animation::Animation() : frames(0), currentFrameIndex(0), currentFrameTime(0.f), realeaseFirstFrame(true) { }

void Animation::Reset() { currentFrameIndex = 0, currentFrameTime = 0.f, realeaseFirstFrame = true; }

void Animation::IncrementFrame() { currentFrameIndex = (currentFrameIndex + 1) % frames.size(); }

void Animation::AddFrame(int textureID, int x, int y, int width, int height, float displayTimeSeconds) {

    FrameData frameData = {textureID, x, y, width, height, displayTimeSeconds};

    frames.push_back(frameData);
}

const FrameData *Animation::GetCurrentFrame() const
{
    if(frames.empty()) return nullptr;
    return &frames[currentFrameIndex];
}

bool Animation::UpdateFrame(float deltaTime)
{
    if(realeaseFirstFrame)
    {
        realeaseFirstFrame = false;
        return true;
    }

    if (frames.size() > 1)
    {
        currentFrameTime += deltaTime;
        if (currentFrameTime >= frames[currentFrameIndex].displayTimeSeconds) {
            currentFrameTime = 0.f;
            IncrementFrame();
            return true;
        }
    }
    return false;
}

