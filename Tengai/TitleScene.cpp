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
	//TODO: �����̽��� ������ �����մϴ�
	if (InputManager::GetKeyDown(VK_SPACE))
	{
		SceneManager::LoadScene<PlayScene>();
	}
}
