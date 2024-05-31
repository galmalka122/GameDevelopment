#include "C_Sprite.h"
#include "Object.h"

C_Sprite::C_Sprite(Object *owner) : Component(owner) { }

void C_Sprite::Load(const std::string &filePath) {

    texture.loadFromFile(filePath);
    sprite.setTexture(texture);

}

void C_Sprite::Draw(Window &window) { window.Draw(sprite); }

void C_Sprite::LateUpdate(float deltaTime) { sprite.setPosition(owner->transform->GetPosition()); }

