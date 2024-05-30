#include "SceneStateMachine.h"

SceneStateMachine::SceneStateMachine() : scenes(0), curScene(0) { }


void SceneStateMachine::ProcessInput() {

    if(curScene){
        curScene->ProcessInput();
    }

}

void SceneStateMachine::Update(float deltaTime) {

    if(curScene){
        curScene->Update(deltaTime);
    }

}

void SceneStateMachine::LateUpdate(float deltaTime) {

    if(curScene){
        curScene->Update(deltaTime);
    }

}

void SceneStateMachine::Draw(Window &window) {

    if(curScene){
        curScene->Draw(window);
    }

}

unsigned int SceneStateMachine::Add(std::shared_ptr<Scene> scene) {

    auto inserted = scenes.insert(std::make_pair(insertedSceneID, scene));

    insertedSceneID++;

    // Initializing the scene
    inserted.first->second->OnCreate();

    return insertedSceneID - 1;

}

void SceneStateMachine::SwitchTo(unsigned int id) {

    auto it = scenes.find(id);

    if(it != scenes.end()){

        // First we deactivate the current active scene
        if(curScene){
            curScene->OnDeactivate();
        }

        // Now we can switch and activate to the new scene
        curScene = it->second;
        curScene->OnActivate();

    }

}

void SceneStateMachine::Remove(unsigned int id) {

    auto it = scenes.find(id);

    if(it != scenes.end()){

        // First we detach the reference
        if(curScene == it->second){
            curScene = nullptr;
        }

        // Now we can destroy and delete the scene
        it->second->OnDestroy();
        scenes.erase(it);

    }

}


