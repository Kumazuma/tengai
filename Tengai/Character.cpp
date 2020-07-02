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
	if (target == nullptr)
	{
		return false;
	}

	RECT myBox = this->simpleCollider + this->position;

	RECT targetBox = target->simpleCollider + target->position;
	RECT outBox;

	if (!IntersectRect(&outBox, &myBox, &targetBox))
	{
		return false;
	}

	for (RECT collider : colliders)
	{
		collider.left += position.x;
		collider.top += position.y;
		collider.right += position.x;
		collider.bottom += position.y;

		for (RECT targetCollider : target->colliders)
		{
			targetCollider.left += target->position.x;
			targetCollider.top += target->position.y;
			targetCollider.right += target->position.x;
			targetCollider.bottom += target->position.y;

			if (IntersectRect(&outBox, &collider, &targetCollider))
			{
				return true;
			}
		}
	}
	


	return false;
}



