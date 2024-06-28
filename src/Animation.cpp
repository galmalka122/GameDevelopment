#include <cstdint>
#include "Animation.h"

Animation::Animation() : frames(0), currentFrameIndex(0), currentFrameTime(0.f), releaseFirstFrame(true) { }

void Animation::Reset() { currentFrameIndex = 0, currentFrameTime = 0.f, releaseFirstFrame = true; }

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
    if(releaseFirstFrame)
    {
        RunActionForCurrentFrame();
        releaseFirstFrame = false;
        return true;
    }

    if (frames.size() > 1)
    {
        currentFrameTime += deltaTime;

        if (currentFrameTime >= frames[currentFrameIndex].displayTimeSeconds)
        {
            currentFrameTime = 0.f;
            IncrementFrame();

            RunActionForCurrentFrame();
            return true;
        }
    }
    return false;
}

void Animation::AddFrameAction(unsigned int frame, AnimationAction action)
{
    if(frame < frames.size())
    {
        auto actionKey = actions.find(frame);

        if(actionKey == actions.end())
        {
            framesWithActions.SetBit(frame);
            actions.insert(std::make_pair(frame, std::vector<AnimationAction>{action}));
        }

        else { actionKey->second.emplace_back(action); }
    }

}

void Animation::RunActionForCurrentFrame() {

    if(!actions.empty())
    {
        if(framesWithActions.GetBit(currentFrameIndex))
        {
            auto actionsToRun = actions.at(currentFrameIndex);
            for(auto f : actionsToRun)
            {
                f();
            }
        }
    }
}

