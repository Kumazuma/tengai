#pragma once
#include "GameObject.h"
class UI :
	public GameObject
{
	// GameObject��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

