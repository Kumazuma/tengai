#pragma once
#include "GameObject.h"
class UI : public GameObject
{
public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

	RECT area;
};

