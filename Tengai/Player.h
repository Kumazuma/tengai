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
private:
	FireState* pFireState;

};

