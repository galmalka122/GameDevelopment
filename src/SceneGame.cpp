#include "SceneGame.h"

SceneGame::SceneGame(WorkingDirectory &workingDir) : workingDir(workingDir)  { }

void SceneGame::OnCreate() {

    player = std::make_shared<Object>();

    // This adds a C_Sprite component into our player.
    auto sprite = player->AddComponent<C_Sprite>();
    sprite->Load(workingDir.Get() + "viking.png");

}

void SceneGame::OnDestroy() {}

void SceneGame::ProcessInput() { input.Update(); }

void SceneGame::Update(float deltaTime) { }

void SceneGame::Draw(Window &window) { player->Draw(window); }
