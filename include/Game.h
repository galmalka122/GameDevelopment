#ifndef Game_h
#define Game_h

#include "Window.h"
#include "WorkingDirectory.h"
#include "Input.h"

class Game
{

public:

	Game();

	~Game() = default;
	
	void Update(); // All the game logic such as movement, A.I., animation...
	
	void LateUpdate(); // Calculations which based on the update method.

	void Draw(); // Draws all entities after the update methods

    void CalculateDeltaTime();

	bool IsRunning();

    void CaptureInput();

private:

	Window window;

    WorkingDirectory workingDir;

    sf::Texture vikingTexture;
    sf::Sprite vikingSprite;

    sf::Clock clock;
    float deltaTime;

    Input input;

};


#endif // !Game_h




