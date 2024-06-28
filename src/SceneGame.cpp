#include "SceneGame.h"

SceneGame::SceneGame(WorkingDirectory &workingDirectory, ResourceAllocator<sf::Texture>& textureAllocator, Window& window) :
    workingDir(workingDirectory), textureAllocator(textureAllocator), mapParser(textureAllocator, workingDirectory),
    window(window) { }

void SceneGame::OnDestroy() {}
void SceneGame::ProcessInput() { input.Update(); }
void SceneGame::LateUpdate(float deltaTime) { objects.LateUpdate(deltaTime); }

void SceneGame::Draw(Window &window)
{
    objects.Draw(window);

#ifdef DEBUG
    Debug::Draw(window);
#endif
}

void SceneGame::OnCreate() {

    std::shared_ptr<Object> player = std::make_shared<Object>();

    // This adds a C_Sprite component into our player.
    auto sprite = player->AddComponent<C_Sprite>();
    sprite->SetTextureAllocator(&textureAllocator);
    sprite->SetDrawLayer(DrawLayer::Entities);

    // This adds a keyboard movement to the player.
    auto movement = player->AddComponent<C_KeyboardMovement>();
    movement->SetInput(&input);

    // Initialize the animation component.
    std::shared_ptr<C_Animation> animation = player->AddComponent<C_Animation>();
    int playerTextureID = textureAllocator.Add(workingDir.Get() + "Player.png");

    // Define the animation's settings manually, later it will be read from a json/xml file.
    const int frameWidth = 64;
    const int frameHeight = 64;
    const int upYFramePos = 512;
    const int leftYFramePos = 576;
    const int downYFramePos = 640;
    const int rightYFramePos = 704;

    const float idleAnimationFrameSeconds = 0.2f;

    std::map<FacingDirection, std::shared_ptr<Animation>> idleAnimations;
    std::shared_ptr<Animation> idleUpAnimation = std::make_shared<Animation>();
    idleUpAnimation->AddFrame(playerTextureID, 0, upYFramePos, frameWidth, frameHeight, 0.f);
    idleAnimations.insert(std::make_pair(FacingDirection::Up, idleUpAnimation));

    std::shared_ptr<Animation> idleDownAnimation = std::make_shared<Animation>();
    idleDownAnimation->AddFrame(playerTextureID, 0, downYFramePos, frameWidth, frameHeight, 0.f);
    idleAnimations.insert(std::make_pair(FacingDirection::Down, idleDownAnimation));

    std::shared_ptr<Animation> idleLeftAnimation = std::make_shared<Animation>();
    idleLeftAnimation->AddFrame(playerTextureID, 0, leftYFramePos, frameWidth, frameHeight, 0.f);
    idleAnimations.insert(std::make_pair(FacingDirection::Left, idleLeftAnimation));

    std::shared_ptr<Animation> idleRightAnimation = std::make_shared<Animation>();
    idleRightAnimation->AddFrame(playerTextureID, 0, rightYFramePos, frameWidth, frameHeight, 0.f);
    idleAnimations.insert(std::make_pair(FacingDirection::Right, idleRightAnimation));

    animation->AddAnimation(AnimationState::Idle, idleAnimations);

    std::shared_ptr<Animation> walkAnimation = std::make_shared<Animation>();

    const int walkingFrameCount = 9;
    const float delayBetweenWalkingFramesSecs = 0.1f;

    std::map<FacingDirection, std::shared_ptr<Animation>> walkingAnimations;
    std::shared_ptr<Animation> walkUpAnimation = std::make_shared<Animation>();

    for (int i = 0; i < walkingFrameCount; ++i) {
        walkUpAnimation->AddFrame(playerTextureID, i * frameWidth, upYFramePos, frameWidth, frameHeight, delayBetweenWalkingFramesSecs);
    }
    walkingAnimations.insert(std::make_pair(FacingDirection::Up, walkUpAnimation));

    std::shared_ptr<Animation> walkDownAnimation = std::make_shared<Animation>();

    for (int i = 0; i < walkingFrameCount; ++i) {
        walkDownAnimation->AddFrame(playerTextureID, i * frameWidth, downYFramePos, frameWidth, frameHeight, delayBetweenWalkingFramesSecs);
    }
    walkingAnimations.insert(std::make_pair(FacingDirection::Down, walkDownAnimation));

    std::shared_ptr<Animation> walkLeftAnimation = std::make_shared<Animation>();

    for (int i = 0; i < walkingFrameCount; ++i) {
        walkLeftAnimation->AddFrame(playerTextureID, i * frameWidth, leftYFramePos, frameWidth, frameHeight, delayBetweenWalkingFramesSecs);
    }
    walkingAnimations.insert(std::make_pair(FacingDirection::Left, walkLeftAnimation));

    std::shared_ptr<Animation> walkRightAnimation = std::make_shared<Animation>();

    for (int i = 0; i < walkingFrameCount; ++i) {
        walkRightAnimation->AddFrame(playerTextureID, i * frameWidth, rightYFramePos, frameWidth, frameHeight, delayBetweenWalkingFramesSecs);
    }
    walkingAnimations.insert(std::make_pair(FacingDirection::Right, walkRightAnimation));

    animation->AddAnimation(AnimationState::Walk, walkingAnimations);

    player->transform->SetPosition(100,700);

    auto collider = player->AddComponent<C_BoxCollider>();
    collider->SetSize(frameHeight * 0.4f, frameHeight * 0.5f);
    collider->SetOffset(0.f, 14.f);
    collider->SetLayer(CollisionLayer::Player);

    auto camera = player->AddComponent<C_Camera>();
    camera->SetWindow(&window);

    objects.Add(player);

    sf::Vector2i mapOffset(-480, 128);

    std::vector<std::shared_ptr<Object>> levelTiles = mapParser.Parse(workingDir.Get() + "House Exterior.tmx", mapOffset);

    objects.Add(levelTiles);

}

void SceneGame::Update(float deltaTime) {

    objects.ProcessRemovals();
    objects.ProcessNewObjects();

    objects.Update(deltaTime);

    Debug::HandleCameraZoom(window, input);

}

