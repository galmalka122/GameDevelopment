#include "SceneGame.h"

SceneGame::SceneGame(WorkingDirectory &workingDir, ResourceAllocator<sf::Texture>& textureAllocator) :
    workingDir(workingDir), textureAllocator(textureAllocator) { }

void SceneGame::OnDestroy() {}
void SceneGame::ProcessInput() { input.Update(); }
void SceneGame::Draw(Window &window) { objects.Draw(window); }
void SceneGame::LateUpdate(float deltaTime) { objects.LateUpdate(deltaTime); }

void SceneGame::OnCreate() {

    std::shared_ptr<Object> player = std::make_shared<Object>();

    // This adds a C_Sprite component into our player.
    auto sprite = player->AddComponent<C_Sprite>();
    sprite->SetTextureAllocator(&textureAllocator);

    // This adds a keyboard movement to the player.
    auto movement = player->AddComponent<C_KeyboardMovement>();
    movement->SetInput(&input);

    // Initialize the animation component.
    std::shared_ptr<C_Animation> animation = player->AddComponent<C_Animation>();
    int vikingTextureID = textureAllocator.Add(workingDir.Get() + "viking.png");

    // Define the animation's settings manually, later it will be read from a json/xml file.
    const int frameWidth = 165;
    const int frameHeight = 145;
    const float idleAnimationFrameSeconds = 0.f;

    std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>();

    // Adds 4 idle animation frames, all same width and height, but with different positions on the sprite.
    idleAnimation->AddFrame(vikingTextureID, 600, 0, frameWidth, frameHeight, idleAnimationFrameSeconds);
    idleAnimation->AddFrame(vikingTextureID, 800, 0, frameWidth, frameHeight, idleAnimationFrameSeconds);
    idleAnimation->AddFrame(vikingTextureID, 0, 145, frameWidth, frameHeight, idleAnimationFrameSeconds);
    idleAnimation->AddFrame(vikingTextureID, 200, 145, frameWidth, frameHeight, idleAnimationFrameSeconds);

    animation->AddAnimation(AnimationState::Idle, idleAnimation);

    objects.Add(player);

}

void SceneGame::Update(float deltaTime) {

    objects.ProcessRemovals();
    objects.ProcessNewObjects();

    objects.Update(deltaTime);

}

