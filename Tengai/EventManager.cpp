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
	auto& _objects = ObjectManager::GetInstance()->objectList;
	for (auto it : _objects)
	{
		for (auto _eventItem : _evenQueue)
		{
			bool cond = _eventItem.objectUid == 0 || (it->uid == _eventItem.objectUid);

			if (it->type == _eventItem.objectType && cond)
			{
				it->HandleEvent(*_eventItem.pEvent);
			}
		}
	}
	for (auto _eventItem : _evenQueue)
	{
		delete _eventItem.pEvent;
	}
	_evenQueue.clear();
}

void EventManager::RegisterObject(GameObject* const pObject)
{

}

void EventManager::UnregisterObject(GameObject* const pObject)
{
}

void EventManager::Release()
{
	auto& _evenQueue = pEventManager->eventQueue;
	
	for (auto _eventItem : _evenQueue)
	{
		delete _eventItem.pEvent;
	}

	delete pEventManager;
}