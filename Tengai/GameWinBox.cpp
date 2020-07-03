#include "stdafx.h"
#include "GameWinBox.h"
#include "SceneManager.h"
#include "TitleScene.h"
GameWinBox::GameWinBox()
{
	position.x = WINDOW_WIDTH / 2;
	position.y = WINDOW_HEIGHT / 2;

	isEnable = false;
	isVisible = false;
	area = { -100,-100,100,100 };
}

GameWinBox::~GameWinBox()
{
}

void GameWinBox::Update()
{
	if (!isEnable) return;
	if (InputManager::GetKeyDown(VK_ESCAPE))
	{
		SceneManager::LoadScene<TitleScene>();
		return;
	}
}

void GameWinBox::Render()
{
	if (!isVisible) return;
	int offset = area.left / 2;
	RenderManager::DrawRect(area + position, RGB(128, 128, 255));
	RenderManager::DrawString(L"³¡!!", position.x + offset, position.y);
}

void GameWinBox::Show()
{
	isEnable = true;
	isVisible = true;
}

void GameWinBox::Hide()
{
	isEnable = false;
	isVisible = false;
	Die();
}
