#pragma once

#include "Character.h"
class Player : public Character
{
public:
	Player();
	virtual ~Player();


	virtual void Update() override;
	virtual void Render() override;

};

