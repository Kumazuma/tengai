#include "stdafx.h"
#include "TitleScene.h"
#include "TestPlayScene.h"


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
