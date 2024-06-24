#ifndef SceneGame_h
#define SceneGame_h

#include "Scene.h"
#include "Input.h"
#include "Debug.h"
#include "WorkingDirectory.h"
#include "Object.h"
#include "C_Camera.h"
#include "C_Sprite.h"
#include "C_KeyboardMovement.h"
#include "C_Animation.h"
#include "ResourceAllocator.h"
#include "ObjectCollection.h"
#include "TileMapParser.h"

class SceneGame : public Scene{

public:

    SceneGame(WorkingDirectory& workingDir, ResourceAllocator<sf::Texture>& textureAllocator, Window& window);

    void OnCreate() override;
    void OnDestroy() override;

    void ProcessInput() override;
    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override;
    void Draw(Window &window) override;

private:

    ObjectCollection objects;

    TileMapParser mapParser;

    Window& window;
    WorkingDirectory& workingDir;
    ResourceAllocator<sf::Texture>& textureAllocator;
    Input input;

};


#endif // SceneGame_h
