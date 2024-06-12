#include "Animation.h"

Animation::Animation(FacingDirection direction) : frames(0), currentFrameIndex(0), currentFrameTime(0.f), direction(direction) { }

void Animation::Reset() { currentFrameIndex = 0, currentFrameTime = 0.f; }

void Animation::IncrementFrame() { currentFrameIndex = (currentFrameIndex + 1) % frames.size(); }

FacingDirection Animation::GetDirection() const { return direction; }

void Animation::AddFrame(int textureID, int x, int y, int width, int height, float displayTimeSeconds) {

    FrameData frameData = {textureID, x, y, width, height, displayTimeSeconds};

    frames.push_back(frameData);
}

const FrameData *Animation::GetCurrentFrame() const {

    if(!frames.empty()) { return &frames[currentFrameIndex]; }

    return nullptr;
}

bool Animation::UpdateFrame(float deltaTime) {

    if(!frames.empty()) {

        currentFrameTime += deltaTime;

        if(currentFrameTime >= frames[currentFrameIndex].displayTimeSeconds){

            currentFrameTime = 0.f;
            IncrementFrame();
            return true;

        }
    }

    return false;
}

void Animation::SetDirection(FacingDirection dir) {

    if(direction != dir){

        direction = dir;
        for (auto& frame : frames){
            // Flips the sprite
            frame.x += frame.width;
            frame.width *= -1;
        }
    }
}

