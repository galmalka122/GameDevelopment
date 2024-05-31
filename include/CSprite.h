#ifndef CSprite_h
#define CSprite_h


#include "Component.h"

class C_Sprite : public Component{

public:

    C_Sprite(Object* owner);

    // Loads the sprite from filePath.
    void Load(const std::string& filePath);

    // Draws the sprite to the screen.
    void Draw(Window& window) override;

private:

    sf::Texture texture;
    sf::Sprite sprite;

};


#endif // CSprite_h
