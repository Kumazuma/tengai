#include "stdafx.h"
#include "MainGame.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "EventManager.h"
#include "Monster.h"
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
}


void MainGame::Run()
{

	InputManager::Update();
	if (pMainGame->isPause)
	{
		//Background클래스의 오브젝트 타입을 ObjectType::Backgound로 하고, 퍼즈 박스만 따로 얻어서 업데이트를 돌린다.
		//
		auto& UIs = ObjectManager::GetInstance()->objectTable[(int)ObjectType::UI];
		for (auto ui : UIs)
		{		
			ui->Update();
		}
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
		RenderManager::Present();
	}
	SceneManager::LastUpdate();
}