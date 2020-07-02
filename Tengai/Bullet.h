#pragma once
#include "Character.h"
class Bullet : public Character
{
	// GameObject을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};

