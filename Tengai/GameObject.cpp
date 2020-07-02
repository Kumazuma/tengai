#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	
}

void GameObject::Die()
{
	isDead = true;
}
