#include "stdafx.h"
#include "BackGround.h"

BackGround* pBackGround = nullptr;

BackGround::BackGround()
{
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
}
