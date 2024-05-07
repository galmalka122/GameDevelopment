#ifndef Game_h
#define Game_h

#include "Window.h"

class Game
{

public:

	Game();

	~Game() = default;
	
	void Update(); // All the game logic such as movement, A.I., animation...
	
	void LateUpdate(); // Calculations which based on the update method.

	void Draw(); // Draws all entities after the update methods 

	bool IsRunning();

private:

	Window window;

};


#endif // !Game_h




