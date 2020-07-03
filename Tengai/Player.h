#pragma once

#include "Character.h"
class Player : public Character
{
public:
	Player();
	virtual ~Player();


	virtual void Update() override;
	virtual void Render() override;
	void OnCollision(const CollisionEvent& event);

	void Move(Direction _direction);
	void Fire();
	void Die() override;
	void Fire2();

private:
	float attackCoolTime = 0.15f;
	float leftTime = 0;
	float attackCoolTime2 = 0.15f;
	float leftTime2 = 0;
};

