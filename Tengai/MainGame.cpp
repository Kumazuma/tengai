#include "stdafx.h"
#include "MainGame.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "EventManager.h"
#include "Monster.h"
#include "PauseBox.h"
#include "BackGround.h"
#include "TestPlayScene.h"
#include "GameOverBox.h"
#include "TitleScene.h"

MainGame* pMainGame = nullptr;

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

MainGame * MainGame::GetInstance()
{
	if (pMainGame == nullptr)
	{
		pMainGame = new MainGame();
	}
	return pMainGame;
}

void MainGame::Initialize()
{
	TimeManager::GetInstance();
	TimeManager::SetFrame(FPS);

	InputManager::GetInstance();
	ObjectManager::GetInstance();
	RenderManager::GetInstance();
	SceneManager::GetInstance();
	EventManager::GetInstance();
	SceneManager::LoadScene<TitleScene>();
}

void MainGame::Release()
{
	SceneManager::Release();
	EventManager::Release();
	TimeManager::Release();
	ObjectManager::Release();
	RenderManager::Release();
	InputManager::Release();
}

void MainGame::Run()
{

	InputManager::Update();
	if (pMainGame->isPause == false)
	{
		ObjectManager::Update();
	}
	ObjectManager::LateUpdate();
	EventManager::LateUpdate();
	if (!TimeManager::SkipFrame())
	{
		RenderManager::Clear();
		BackGround::GetInstance()->Render();
		ObjectManager::Render();
		RenderManager::Present();
	}
	SceneManager::LastUpdate();
}

void MainGame::Pause()
{
	pMainGame->isPause = true;
}

void MainGame::Resume()
{
	pMainGame->isPause = false;
}

void MainGame::Shutdown()
{
	PostQuitMessage(0);
}
