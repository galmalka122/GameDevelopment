#include "SceneGame.h"

SceneGame::SceneGame(WorkingDirectory &workingDirectory, ResourceAllocator<sf::Texture>& textureAllocator) :
    workingDir(workingDirectory), textureAllocator(textureAllocator), mapParser(textureAllocator, workingDirectory) { }

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
    const float idleAnimationFrameSeconds = 0.2f;

    std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>(FacingDirection::Right);

    // Adds 4 idle animation frames, all same width and height, but with different positions on the sprite.
    idleAnimation->AddFrame(vikingTextureID, 600, 0, frameWidth, frameHeight, idleAnimationFrameSeconds);
    idleAnimation->AddFrame(vikingTextureID, 800, 0, frameWidth, frameHeight, idleAnimationFrameSeconds);
    idleAnimation->AddFrame(vikingTextureID, 0, 145, frameWidth, frameHeight, idleAnimationFrameSeconds);
    idleAnimation->AddFrame(vikingTextureID, 200, 145, frameWidth, frameHeight, idleAnimationFrameSeconds);

    animation->AddAnimation(AnimationState::Idle, idleAnimation);

    std::shared_ptr<Animation> walkAnimation = std::make_shared<Animation>(FacingDirection::Right);

    const float walkAnimationFrameSeconds = 0.15f;

    // Adds 4 idle animation frames, all same width and height, but with different positions on the sprite.
    walkAnimation->AddFrame(vikingTextureID, 600, 290, frameWidth, frameHeight, walkAnimationFrameSeconds);
    walkAnimation->AddFrame(vikingTextureID, 800, 290, frameWidth, frameHeight, walkAnimationFrameSeconds);
    walkAnimation->AddFrame(vikingTextureID, 0, 435, frameWidth, frameHeight, walkAnimationFrameSeconds);
    walkAnimation->AddFrame(vikingTextureID, 200, 435, frameWidth, frameHeight, walkAnimationFrameSeconds);
    walkAnimation->AddFrame(vikingTextureID, 400, 435, frameWidth, frameHeight, walkAnimationFrameSeconds);

    animation->AddAnimation(AnimationState::Walk, walkAnimation);

    objects.Add(player);

    sf::Vector2i mapOffset(-480, 128);

    std::vector<std::shared_ptr<Object>> levelTiles = mapParser.Parse(workingDir.Get() + "Test Map 1.tmx", mapOffset);

    objects.Add(levelTiles);

}

void SceneGame::Update(float deltaTime) {

    objects.ProcessRemovals();
    objects.ProcessNewObjects();

    objects.Update(deltaTime);

}

