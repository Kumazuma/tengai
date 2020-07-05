#include "stdafx.h"
#include "TitleUI.h"

TitleUI::TitleUI()
{
	this->position = { 50,100 };

	UI* ui = new UI;
	ui->pParent = (GameObject*)this;
	ui->localPosition = { 0,0 };
	ui->area = { 0,0,150,50 };
	uis.push_back(ui);
	ui = new UI;
	ui->pParent = (GameObject*)this;
	ui->localPosition = { 50,0 };
	ui->area = { 0,0,50,150 };
	uis.push_back(ui);
	ui = new UI;
	ui->pParent = (GameObject*)this;
	ui->localPosition = { 0,0 };
	ui->area = { 0,0,150,50 };
	uis.push_back(ui);
}

TitleUI::~TitleUI()
{
	auto iter = uis.begin();
	auto end = uis.end();
	for (; iter != end;)
	{
		delete (*iter);
		iter = uis.erase(iter);
	}
}

void TitleUI::Update()
{
	for (UI* ui : uis)
	{
		ui->position = ui->localPosition + ui->pParent->position;
	}
}

void TitleUI::Render()
{
	for (UI* ui : uis)
	{
		RenderManager::DrawRect(ui->area + ui->position, RGB(255, 0, 0), RGB(255, 0, 0));
	}
}

PressAnyKeyUI::PressAnyKeyUI()
{
}

PressAnyKeyUI::~PressAnyKeyUI()
{
}

void PressAnyKeyUI::Update()
{
}

void PressAnyKeyUI::Render()
{
}
