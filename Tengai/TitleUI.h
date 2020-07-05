#pragma once
#include "UI.h"
class TitleUI : public UI
{
public:
	TitleUI();
	~TitleUI();

	virtual void Update() override;
	virtual void Render() override;

	list<UI*> uis;
};

class PressAnyKeyUI : public UI
{
public:
	PressAnyKeyUI();
	~PressAnyKeyUI();

	virtual void Update() override;
	virtual void Render() override;
};

