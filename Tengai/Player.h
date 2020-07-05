#pragma once

#include "Character.h"
class FireState;
class Player : public Character
{
public:
	Player();
	virtual ~Player();
	virtual void Update() override;
	virtual void Render() override;
	void OnCollision(const CollisionEvent& event);
	void Move(Direction _direction);
	void Die() override;

	void SinWave();
	void SpecialMove();
	void UpdateSpecialMove();
private:
	FireState* pFireState;
	float sinCoolTime = 0.1f;
	float sinLeftTime = 0.f;
	float coolTime = 5.f;
	float leftTime = 0.f;
	float tick = 0.f;
	float interval = 0.1f;
	int fireCount = 0;
	bool specialMoveFlag = false;
	
};

