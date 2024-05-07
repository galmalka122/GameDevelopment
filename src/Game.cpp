#include "Game.h"


Game::Game() : window("First Look") {}

/****************************************************************************
*             This method is where we put all the game logic.               *
/****************************************************************************/
void Game::Update()
{
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

	window.EndDraw();
}


bool Game::IsRunning()
{
	return window.IsOpen();
}
