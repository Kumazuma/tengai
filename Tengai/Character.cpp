#include "stdafx.h"
#include "Character.h"

void Character::Update()
{
}

void Character::Render()
{
}

bool Character::Collision(const GameObject* _target)
{
	const Character* target = dynamic_cast<const Character*>(_target);
	if (target == nullptr) return false;
	if (target->type == type) return false;

	RECT myBox = this->simpleCollider + this->position;
	RECT targetBox = target->simpleCollider + target->position;
	RECT outBox;

	if (!IntersectRect(&outBox, &myBox, &targetBox)) return false;

	for (RECT collider : this->colliders)
	{
		collider = collider + position;

		for (RECT targetCollider : target->colliders)
		{
			targetCollider = targetCollider + target->position;

			if (IntersectRect(&outBox, &collider, &targetCollider))
			{
				return true;
			}
		}
	}
	


	return false;
}



