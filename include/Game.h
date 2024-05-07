#ifndef GAME_H
#define GAME_H

#include "Window.h"

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

};


#endif // !GAME_H




