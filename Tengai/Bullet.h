#pragma once
#include "Character.h"
class Bullet : public Character
{
	// GameObject��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

