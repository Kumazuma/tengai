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

void GameObject::HandleEvent(const Event& _event)
{
	EventHandler _handler = handlerTable[(int)_event.id];
	if (_handler == nullptr)
	{
		return;
	}
	(this->*_handler)(_event);
}

void GameObject::_Bind(EventId id, EventHandler handler)
{
	handlerTable[(int)id] = handler;
}