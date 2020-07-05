#pragma once
#include "UI.h"
class TitleUI : public UI
{
public:
	TitleUI();
	~TitleUI();

	virtual void Update() override;
	virtual void Render() override;
};

class PressAnyKeyUI : public UI
{
public:
	PressAnyKeyUI();
	~PressAnyKeyUI();

	virtual void Update() override;
	virtual void Render() override;

	float tick = 0.f;
	float interval = 0.5f;
	bool isRender = false;
};

