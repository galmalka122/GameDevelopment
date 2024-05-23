#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "WorkingDirectory.h"

class Game
{

public:

	Game();
	
	void Update(); // All the game logic such as movement, A.I., animation...
	
	void LateUpdate(); // Calculations which based on the update method.

	void Draw(); // Draws all entities after the update methods 

	bool IsRunning();

private:

	Window window;

    WorkingDirectory workingDir;

    sf::Texture vikingTexture;
    sf::Sprite vikingSprite;

};


#endif // !GAME_H




