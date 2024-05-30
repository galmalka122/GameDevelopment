#ifndef SceneSplashScreen_h
#define SceneSplashScreen_h

#include "WorkingDirectory.h"
#include "SceneStateMachine.h"

class SceneSplashScreen : public Scene {

public:

    SceneSplashScreen(WorkingDirectory& workingDir, SceneStateMachine& sceneStateMachine, Window& window);

    // Scene methods
    void OnCreate() override;
    void OnDestroy() override;
    void OnActivate() override;
    void Update(float deltaTime) override;
    void Draw(Window& window) override;

    void SetSwitchToScene(unsigned int id);



private:

    sf::Texture splashTexture;
    sf::Sprite splashSprite;

    WorkingDirectory& workingDir;
    SceneStateMachine& sceneStateMachine;
    Window& window;

    // The length of the scene
    float showForSeconds;

    // The time that passed
    float currentSeconds;

    // When the scene ends, this holds the ID of the next scene
    unsigned int switchToState;

};


#endif // SceneSplashScreen_h
