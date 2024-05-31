#include "Game.h"
#include "SceneSplashScreen.h"
#include "SceneGame.h"
#include "Object.h"


Game::Game() : window("First Look") {

    std::shared_ptr<SceneSplashScreen> splashScreen = std::make_shared<SceneSplashScreen>(workingDir, sceneManager,
                                                                                          window, textureAllocator);

    std::shared_ptr<SceneGame> sceneGame = std::make_shared<SceneGame>(workingDir, textureAllocator);

    unsigned int splashScreenID = sceneManager.Add(splashScreen);
    unsigned int gameSceneID = sceneManager.Add(sceneGame);

    splashScreen->SetSwitchToScene(gameSceneID);
    sceneManager.SwitchTo(splashScreenID);

    deltaTime = clock.restart().asSeconds();



}

/****************************************************************************
*             This method is where we put all the game logic.               *
/****************************************************************************/
void Game::Update()
{

    window.Update();
    sceneManager.Update(deltaTime);

}


/******************************************************************************
* This method is executed right after the Update method, for any calculations *
*                    that should rely on this updates.                        *
******************************************************************************/
void Game::LateUpdate(){ sceneManager.LateUpdate(deltaTime); }


/*******************************************************************************
* This method is executed after all updates methods are finished and draws all *
*                          the entities to the screen.                         *
*******************************************************************************/
void Game::Draw()
{
	window.BeginDraw();

    sceneManager.Draw(window);

	window.EndDraw();
}


bool Game::IsRunning() { return window.IsOpen(); }

void Game::CalculateDeltaTime() { deltaTime = clock.restart().asSeconds(); }

void Game::CaptureInput() { sceneManager.ProcessInput(); }
