#include "SceneSplashScreen.h"

SceneSplashScreen::SceneSplashScreen(WorkingDirectory &workingDir, SceneStateMachine &sceneStateMachine,Window &window,
    ResourceAllocator<sf::Texture>& allocator) : window(window), workingDir(workingDir), switchToState(0),
    sceneStateMachine(sceneStateMachine), currentSeconds(0.f), showForSeconds(3.f), allocator(allocator) { }

void SceneSplashScreen::OnCreate() {

    int textureID = allocator.Add(workingDir.Get() + "that_games_guy_logo.png");

    if(textureID >= 0){

        std::shared_ptr<sf::Texture> texture = allocator.Get(textureID);
        splashSprite.setTexture(*texture);

        sf::FloatRect spriteSize = splashSprite.getLocalBounds();

        // The origin will be the center of the image
        splashSprite.setOrigin(spriteSize.width * 0.5f, spriteSize.height * 0.5f);
        splashSprite.setScale(0.5f, 0.5f);

        // Position the sprite in the centre of the window
        sf::Vector2u windowCenter = window.GetCenter();
        splashSprite.setPosition(windowCenter.x, windowCenter.y);

        }
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
