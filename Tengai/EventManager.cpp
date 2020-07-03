#include"stdafx.h"
#include"EventManager.h"
#include"event.h"
#include"ObjectManager.h"

EventManager* pEventManager = nullptr;
EventManager::EventManager():
	eventQueue{}
{
}
void EventManager::Broadcast(Event* _pEvent, ObjectType _type, int _uid)
{
	pEventManager->eventQueue.push_back({ _pEvent, _uid , _type });
	pEventManager->events.push_back(_pEvent);
}
void EventManager::Broadcast(GameObject* const obj, Event* _pEvent)
{
	obj->eventQueue.push_back(_pEvent);
	pEventManager->events.push_back(_pEvent);
}
EventManager* EventManager::GetInstance()
{
	if (pEventManager == nullptr)
	{
		pEventManager = new EventManager();
		pEventManager->eventQueue.reserve(1024);
	}
	return pEventManager;
}
void EventManager::Initialize()
{

}

void EventManager::LateUpdate()
{
	auto& _evenQueue = pEventManager->eventQueue;
	for (auto obj : ObjectManager::GetInstance()->objectTable[(int)ObjectType::BULLET])
	{
		for (auto event : obj->eventQueue)
		{
			obj->HandleEvent(*event);
		}
		obj->eventQueue.clear();
	}
	for (auto obj : ObjectManager::GetInstance()->objectTable[(int)ObjectType::MONSTER])
	{
		for (auto event : obj->eventQueue)
		{
			obj->HandleEvent(*event);
		}
		obj->eventQueue.clear();
	}
	for (auto obj : ObjectManager::GetInstance()->objectTable[(int)ObjectType::PLAYER])
	{
		for (auto event : obj->eventQueue)
		{
			obj->HandleEvent(*event);
		}
		obj->eventQueue.clear();
	}
	for (auto obj : ObjectManager::GetInstance()->objectTable[(int)ObjectType::ITEM])
	{
		for (auto event : obj->eventQueue)
		{
			obj->HandleEvent(*event);
		}
		obj->eventQueue.clear();
	}
	for (auto _eventItem : _evenQueue)
	{
		auto& objs = ObjectManager::GetInstance()->objectTable[(int)_eventItem.objectType];
		for (auto it : objs)
		{
			it->HandleEvent(*_eventItem.pEvent);
		}
	}
	for (auto _eventItem : pEventManager->events)
	{
		delete _eventItem;
	}
	_evenQueue.clear();
	pEventManager->events.clear();
}

void EventManager::RegisterObject(GameObject* const pObject)
{

}

void EventManager::UnregisterObject(GameObject* const pObject)
{
}

void EventManager::Release()
{
	if (pEventManager != nullptr)
	{
		auto& _evenQueue = pEventManager->eventQueue;

		for (auto _eventItem : _evenQueue)
		{
			delete _eventItem.pEvent;
		}

		delete pEventManager;
		pEventManager = nullptr;
	}
	
}