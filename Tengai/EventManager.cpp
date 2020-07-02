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
	pEventManager->eventQueue.push({ _pEvent, _uid , _type });
}
EventManager* EventManager::GetInstance()
{
	if (pEventManager == nullptr)
	{
		pEventManager = new EventManager();
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
	while (_evenQueue.empty() == false)
	{
		auto _eventItem = _evenQueue.front();
		_evenQueue.pop();
		for (auto it : _objects)
		{
			bool cond = _eventItem.objectUid == 0 || (it->uid == _eventItem.objectUid);
			if (it->type == _eventItem.objectType && cond)
			{
				it->HandleEvent(*_eventItem.pEvent);
			}
		}
		//TODO:
		//type:

		delete _eventItem.pEvent;
	}
}

void EventManager::Release()
{
	auto& _evenQueue = pEventManager->eventQueue;
	
	while (_evenQueue.empty() == false)
	{
		auto _eventItem = _evenQueue.front();
		_evenQueue.pop();
		delete _eventItem.pEvent;
	}

	delete pEventManager;
}