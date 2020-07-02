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

	RECT myBox = 
	{
		simpleCollider.left + position.x,
		simpleCollider.top + position.y,
		simpleCollider.right + position.x,
		simpleCollider.bottom + position.y
	};

	RECT targetBox =
	{
		target->simpleCollider.left + target->position.x,
		target->simpleCollider.top + target->position.y,
		target->simpleCollider.right + target->position.x,
		target->simpleCollider.bottom + target->position.y
	};

	if (!IntersectRect(nullptr, &myBox, &targetBox))
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

			if (IntersectRect(nullptr, &collider, &targetCollider))
			{
				return true;
			}
		}
	}
	


	return false;
}



