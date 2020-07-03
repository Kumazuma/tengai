#pragma once
#include "GameObject.h"
class UI : public GameObject
{
public:
	// GameObject을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

	RECT area;
	COLORREF color = RGB(255, 255, 255);
};

