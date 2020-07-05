#include "stdafx.h"
#include "TitleScene.h"
#include "TestPlayScene.h"


TitleScene::TitleScene()
{
	titleUI = ObjectManager::CreateObject(ObjectType::TITLE_UI);
	pressUI = ObjectManager::CreateObject(ObjectType::PRESSKEY_UI);
}

TitleScene::~TitleScene()
{
	ObjectManager::DeleteObject(titleUI);
	ObjectManager::DeleteObject(pressUI);
}

void TitleScene::OnLoaded()
{
	
}

void TitleScene::OnUnloaded()
{
	
}

void TitleScene::Update()
{
	//TODO: 스페이스를 누르면 시작합니다
	if (InputManager::GetKeyDown(VK_SPACE))
	{
		SceneManager::LoadScene<PlayScene>();
	}
}
