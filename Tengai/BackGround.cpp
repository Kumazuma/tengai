#include "stdafx.h"
#include "BackGround.h"

BackGround* pBackGround = nullptr;

BackGround::BackGround()
{
	position.x = 0;
	position.y = 0;
	area = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
	color = RGB(128, 255, 255);

	
	for (int i = 0; i < 4; i++)
	{
		Transform pos = { float(WINDOW_WIDTH + (i * 300)), float(rand() % 200) };
		UI* cloud = new Cloud;
		cloud->position = pos;
		clouds.push_back(cloud);
	}
}

BackGround::~BackGround()
{
	auto iter = clouds.begin();
	auto end = clouds.end();
	for (; iter != end;)
	{
		delete (*iter);
		iter = clouds.erase(iter);
	}
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
	auto iter = clouds.begin();
	auto end = clouds.end();
	for (; iter != end; ++iter)
	{
		(*iter)->Update();
	}
}

void BackGround::Render()
{
	RenderManager::DrawRect(area, color, color);

	auto iter = clouds.begin();
	auto end = clouds.end();
	for (; iter != end; ++iter)
	{
		(*iter)->Render();
	}
}

Cloud::Cloud()
{
	position.x = 400;
	position.y = 0;
	color = RGB(255, 255, 255);
	area = { -30,-30,30,30 };
	
}

Cloud::~Cloud()
{
}

void Cloud::Update()
{
	position.x -= cloudSpeed * TimeManager::DeltaTime();

	if (position.x < -area.right-100)
	{
		position.x = WINDOW_WIDTH + 200;
		position.y = float(100 + rand() % 200);
	}
}

void Cloud::Render()
{
	float radian;
	Transform pos;
	COLORREF colorref;
	for (int i = 0; i < 10; i++)
	{
		pos = position;
		radian = 2.f * PI * i / 10.f;
		pos.x += 50.f * cosf(radian);
		pos.y += 20.f * sinf(radian);
		colorref = RGB(200 + (i * 5), 200 + (i * 5), 200 + (i * 5));
		RenderManager::DrawCircle(area + pos, colorref, colorref);
	}
	
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
