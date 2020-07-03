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
private:
	float attackCoolTime = 0.15f;
	float leftTime = 0;
};

