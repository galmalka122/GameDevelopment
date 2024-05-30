#ifndef SceneStateMachine_h
#define SceneStateMachine_h

#include <memory>
#include <unordered_map>

#include "Scene.h"
#include "Window.h"

class SceneStateMachine {

public:

    SceneStateMachine();

    // Update, ProcessInput, LateUpdate, and Draw, simply calls the active scene's functions("pass through")
    void Update(float deltaTime);
    void ProcessInput();
    void LateUpdate(float deltaTime);
    void Draw(Window& window);

    // Adds a scene to the state machine and returns the scenes ID
    unsigned int Add(std::shared_ptr<Scene> scene);

    // Transition from one scene to another
    void SwitchTo(unsigned int id);

    // Removes a scene from the state machine
    void Remove(unsigned int id);

private:

    // We pair each scene with a unique ID
    std::unordered_map<unsigned int, std::shared_ptr<Scene>> scenes;

    // Reference to the current scene
    std::shared_ptr<Scene> curScene;

    // this will be incremented each time a new scene is added
    unsigned int insertedSceneID;

};


#endif // SceneStateMachine_h
