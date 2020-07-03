#include "stdafx.h"
#include "MainGame.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "EventManager.h"
#include "Monster.h"
#include "PauseBox.h"
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
	ObjectManager::CreateObject(ObjectType::PLAYER);
	Monster* pMonster = (Monster *)ObjectManager::CreateObject(ObjectType::MONSTER);
	pMonster->Initialize(MonsterType::BOSS, { WINDOW_WIDTH, WINDOW_HEIGHT/2 });
	pMonster = (Monster*)ObjectManager::CreateObject(ObjectType::MONSTER);
	pMonster->Initialize(MonsterType::MOB02, { WINDOW_WIDTH, WINDOW_HEIGHT/ 3 });
	pMonster = (Monster*)ObjectManager::CreateObject(ObjectType::MONSTER);
	pMonster->Initialize(MonsterType::MOB01, { WINDOW_WIDTH, WINDOW_HEIGHT});
}

void MainGame::Release()
{
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
