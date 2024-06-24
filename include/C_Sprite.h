#ifndef CSprite_h
#define CSprite_h


#include "Component.h"
#include "ResourceAllocator.h"
#include "C_Drawable.h"

class C_Sprite : public Component, public C_Drawable {

public:

    explicit C_Sprite(Object* owner);

    // Loads the sprite from filePath.
    void Load(const std::string& filePath);
    void Load(int id);

    void SetTextureAllocator(ResourceAllocator<sf::Texture>* allocator);
    void SetTextureRect(int x, int y, int width, int height);
    void SetTextureRect(const sf::IntRect& rect);
    void SetScale(float x, float y);

    void LateUpdate(float deltaTime) override;

    bool ContinueToDraw() const override;

    // Draws the sprite to the screen.
    void Draw(Window& window) override;

private:

    ResourceAllocator<sf::Texture>* allocator;
    sf::Sprite sprite;

    int currentTextureID;

};


#endif // CSprite_h
