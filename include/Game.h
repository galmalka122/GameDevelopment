#ifndef GAME_H
#define GAME_H

class Game
{


public:

	
	void Update(); // All the game logic such as movement, A.I., animation...
	
	void LateUpdate(); // Calculations which based on the update method.

	void Draw(); // Draws all entities after the update methods 

	bool IsRunning();


};


#endif // !GAME_H




