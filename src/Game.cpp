#include "Game.h"


Game::Game() : window("First Look") {

    vikingTexture.loadFromFile(workingDir.Get() + "viking.png");
    vikingSprite.setTexture(vikingTexture);

    deltaTime = clock.restart().asSeconds();

}

/****************************************************************************
*             This method is where we put all the game logic.               *
/****************************************************************************/
void Game::Update()
{

    const sf::Vector2f& spritePos = vikingSprite.getPosition();
    const int pixelsToMovePerSec = 100;
    const float frameMovement = pixelsToMovePerSec * deltaTime;

    vikingSprite.setPosition(spritePos.x + 1 * frameMovement, spritePos.y);

	window.Update();
}


/******************************************************************************
* This method is executed right after the Update method, for any calculations *
*                    that should rely on this updates.                        *
******************************************************************************/
void Game::LateUpdate()
{
}


/*******************************************************************************
* This method is executed after all updates methods are finished and draws all *
*                          the entities to the screen.                         *
*******************************************************************************/
void Game::Draw()
{
	window.BeginDraw();

    window.Draw(vikingSprite);

	window.EndDraw();
}


bool Game::IsRunning()
{
	return window.IsOpen();
}

void Game::CalculateDeltaTime() {

    deltaTime = clock.restart().asSeconds();

}
