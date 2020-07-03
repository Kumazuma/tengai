#include "stdafx.h"
#include "GameOverBox.h"
#include "TitleScene.h"

GameOverBox* pGameOverBox = nullptr;

GameOverBox::GameOverBox()
{
	position.x = WINDOW_WIDTH / 2;
	position.y = WINDOW_HEIGHT / 2;

	isEnable = false;
	isVisible = false;
	area = { -100,-100,100,100 };
}

GameOverBox::~GameOverBox()
{
}

GameOverBox* GameOverBox::GetInstance()
{
	if (pGameOverBox == nullptr)
	{
		pGameOverBox = new GameOverBox;
	}
	return pGameOverBox;
}

void GameOverBox::Release()
{
	delete pGameOverBox;
}

void GameOverBox::Update()
{
	if (!isEnable) return;

	if (InputManager::GetKeyDown(VK_ESCAPE))
	{
		SceneManager::LoadScene<TitleScene>();
		return;
	}
}

void GameOverBox::Render()
{
	if (!isVisible) return;
	int offset = area.left / 2;
	RenderManager::DrawRect(area + position, RGB(255, 0, 0));
	RenderManager::DrawString(L"게 임 오 버", position.x +offset , position.y);
}

void GameOverBox::Show()
{
	pGameOverBox->isEnable = true;
	pGameOverBox->isVisible = true;
}

void GameOverBox::Hide()
{
	pGameOverBox->isEnable = false;
	pGameOverBox->isVisible = false;
}
