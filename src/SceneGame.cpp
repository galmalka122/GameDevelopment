#include "SceneGame.h"

SceneGame::SceneGame(WorkingDirectory &workingDir, ResourceAllocator<sf::Texture>& textureAllocator) :
    workingDir(workingDir), textureAllocator(textureAllocator) { }

void SceneGame::OnCreate() {

    player = std::make_shared<Object>();

    // This adds a C_Sprite component into our player.
    auto sprite = player->AddComponent<C_Sprite>();
    sprite->SetTextureAllocator(&textureAllocator);
    sprite->Load(workingDir.Get() + "viking.png");

    // This adds a keyboard movement to the player.
    auto movement = player->AddComponent<C_KeyboardMovement>();
    movement->SetInput(&input);

}

void SceneGame::OnDestroy() {}

void SceneGame::ProcessInput() { input.Update(); }

void SceneGame::Update(float deltaTime) { player->Update(deltaTime); }

void SceneGame::Draw(Window &window) { player->Draw(window); }

void SceneGame::LateUpdate(float deltaTime) { player->LateUpdate(deltaTime); }
