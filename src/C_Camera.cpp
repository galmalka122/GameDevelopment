#include "C_Camera.h"
#include "Object.h"

C_Camera::C_Camera(Object *owner) : Component(owner) { }
void C_Camera::SetWindow(Window *gameWindow) { window = gameWindow; }

void C_Camera::LateUpdate(float deltaTime) {

    if(window){

        sf::View view = window->GetView();

        const sf::Vector2f& playerPos = owner->transform->GetPosition();
        view.setCenter(playerPos.x, playerPos.y);

        window->SetView(view);
    }
}


