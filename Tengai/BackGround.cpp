#include "stdafx.h"
#include "BackGround.h"

BackGround* pBackGround = nullptr;

BackGround::BackGround()
{
	position.x = 0;
	position.y = 0;
	area = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
	color = RGB(128, 255, 255);

	
}

BackGround::~BackGround()
{
}

BackGround* BackGround::GetInstance()
{
	if (pBackGround == nullptr)
	{
		pBackGround = new BackGround;
	}
	return pBackGround;
}

void BackGround::Release()
{
	delete pBackGround;
}

void BackGround::Update()
{
}

void BackGround::Render()
{
	RenderManager::DrawRect(area, color, color);

}

Cloud::Cloud()
{
	position.x = 400;
	position.y = 100;
	color = RGB(255, 255, 255);
	area = { -30,-30,30,30 };
}

Cloud::~Cloud()
{
}

void Cloud::Update()
{

}

void Cloud::Render()
{
	RenderManager::DrawRect(area + position, color, color);
}

Tree::Tree()
{
}

Tree::~Tree()
{
}

void Tree::Update()
{
}

void Tree::Render()
{
}
