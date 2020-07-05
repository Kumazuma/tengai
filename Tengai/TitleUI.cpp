#include "stdafx.h"
#include "TitleUI.h"

TitleUI::TitleUI()
{
	this->position = { WINDOW_WIDTH/2,0};

}

TitleUI::~TitleUI()
{
}

void TitleUI::Update()
{
	if(this->position.y < WINDOW_HEIGHT/3)
		this->position.y += 2;
}

void TitleUI::Render()
{
	RenderManager::DrawString(L"TENGAI", position.x - 100, position.y, NULL, 50, RGB(255, 0, 0));
}

PressAnyKeyUI::PressAnyKeyUI()
{
	this->position = { WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 };
}

PressAnyKeyUI::~PressAnyKeyUI()
{
}

void PressAnyKeyUI::Update()
{
	tick += TimeManager::DeltaTime();
	
	if (tick >= interval)
	{
		isRender = !isRender;
		tick = 0;
	}
}

void PressAnyKeyUI::Render()
{
	if (isRender)
	{
		RenderManager::DrawString(L"PRESS ANY KEY", position.x - 50, position.y);
	}
}
