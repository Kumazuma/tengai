#include "stdafx.h"
#include "MainGame.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "EventManager.h"
#include "Monster.h"
#include "PauseBox.h"
#include "TestPlayScene.h"
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
	SceneManager::LoadScene<PlayScene>();

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
	if (pMainGame->isPause)
	{
		PauseBox::GetInstance()->Update();
	}
	else
	{
		ObjectManager::Update();
	}
	ObjectManager::LateUpdate();
	EventManager::LateUpdate();
	if (!TimeManager::SkipFrame())
	{
		RenderManager::Clear();
		ObjectManager::Render();
		PauseBox::GetInstance()->Render();
		RenderManager::Present();
	}
	SceneManager::LastUpdate();
}

void MainGame::Pause()
{
	pMainGame->isPause = true;
	PauseBox::Show();
}

void MainGame::Resume()
{
	pMainGame->isPause = false;
	PauseBox::Hide();
}

void MainGame::Shutdown()
{
	PostQuitMessage(0);
}
