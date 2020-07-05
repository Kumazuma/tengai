#include "stdafx.h"
#include "TitleScene.h"
#include "TestPlayScene.h"


TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::OnLoaded()
{
	titleUI = ObjectManager::CreateObject(ObjectType::TITLE_UI);
	pressUI = ObjectManager::CreateObject(ObjectType::PRESSKEY_UI);
	MainGame::Resume();
}

void TitleScene::OnUnloaded()
{
	ObjectManager::DeleteObject(titleUI);
	ObjectManager::DeleteObject(pressUI);
}

void TitleScene::Update()
{
	//TODO: 스페이스를 누르면 시작합니다
	if (InputManager::GetKeyDown(VK_SPACE))
	{
		SceneManager::LoadScene<PlayScene>();
	}
}
