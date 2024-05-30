#include "SceneSplashScreen.h"

SceneSplashScreen::SceneSplashScreen(WorkingDirectory &workingDir, SceneStateMachine &sceneStateMachine,Window &window):
    window(window), workingDir(workingDir), sceneStateMachine(sceneStateMachine), switchToState(0),
    currentSeconds(0.f), showForSeconds(3.f){ }

void SceneSplashScreen::OnCreate() {

    splashTexture.loadFromFile(workingDir.Get() + "that_games_guy_logo.png");
    splashSprite.setTexture(splashTexture);

    sf::FloatRect spriteSize = splashSprite.getLocalBounds();

    // The origin will be the center of the image
    splashSprite.setOrigin(spriteSize.width * 0.5f, spriteSize.height * 0.5f);
    splashSprite.setScale(0.5f, 0.5f);

    // Position the sprite in the centre of the window
    sf::Vector2u windowCenter = window.GetCenter();
    splashSprite.setPosition(windowCenter.x, windowCenter.y);

}

void SceneSplashScreen::OnDestroy() { }

void SceneSplashScreen::OnActivate() { currentSeconds = 0.f; }

void SceneSplashScreen::Update(float deltaTime) {

    currentSeconds += deltaTime;

    if(currentSeconds >= showForSeconds){
        sceneStateMachine.SwitchTo(switchToState);
    }

}

void SceneSplashScreen::Draw(Window &window) { window.Draw(splashSprite); }

void SceneSplashScreen::SetSwitchToScene(unsigned int id) { switchToState = id; }
