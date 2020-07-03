#include "stdafx.h"
#include "GameOverBox.h"
#include "TitleScene.h"

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
	//TODO: ESCŰ�� ������ Ÿ��Ʋ�� �Ѿ�ϴ�.
	if (!isVisible) return;
	int offset = area.left / 2;
	RenderManager::DrawRect(area + position, RGB(255, 0, 0));
	RenderManager::DrawString(L"�� �� �� ��", position.x +offset , position.y);
}

void GameOverBox::Show()
{

	isEnable = true;
	isVisible = true;
}

void GameOverBox::Hide()
{
	isEnable = false;
	isVisible = false;
	Die();
}
