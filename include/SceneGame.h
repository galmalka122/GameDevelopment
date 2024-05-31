#ifndef SceneGame_h
#define SceneGame_h

#include "Scene.h"
#include "Input.h"
#include "WorkingDirectory.h"
#include "Object.h"
#include "C_Sprite.h"

class SceneGame : public Scene{

public:

    SceneGame(WorkingDirectory& workingDir);

    void OnCreate() override;
    void OnDestroy() override;

    void ProcessInput() override;
    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override;
    void Draw(Window &window) override;

private:

    std::shared_ptr<Object> player;

    WorkingDirectory& workingDir;
    Input input;

};


#endif // SceneGame_h
