#include "stdafx.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"
#include "UI.h"
#include "Bullet.h"

ObjectManager* pObjectManager = nullptr;
int lastUid = 0;

ObjectManager::ObjectManager()
{
	
}

ObjectManager::~ObjectManager()
{

}

ObjectManager * ObjectManager::GetInstance()
{
	if (pObjectManager == nullptr)
	{
		pObjectManager = new ObjectManager;
	}
	return pObjectManager;
}

GameObject * ObjectManager::CreateObject(ObjectType _type)
{
	GameObject* pObj = nullptr;
	switch (_type)
	{
	case ObjectType::MONSTER:
		pObj = new Monster();
		break;
	case ObjectType::PLAYER:
	{
		if (pObjectManager->pPlayer != nullptr)
		{
			return pObjectManager->pPlayer;
		}
		pObjectManager->pPlayer = new Player();
		pObj = pObjectManager->pPlayer;
		break;
	}
	case ObjectType::BULLET:
		pObj = new Bullet();
		break;
	case ObjectType::UI:
		pObj = new UI();
		break;
	default:
		return nullptr;
	}

	pObj->uid = ++lastUid;
	pObjectManager->objectList.insert(pObj);

	return pObj;
}

bool ObjectManager::DeleteObject(GameObject * _target)
{
	auto& objList = pObjectManager->objectList;
	auto target = objList.find(_target);
	if (target != objList.end())
	{
		_target->Die();
		return true;
	}
	return false;
}

void ObjectManager::DestroyAll()
{
	for (auto iter : pObjectManager->objectList)
	{
		iter->Die();
	}
}

void ObjectManager::DestroyAll(ObjectType _type)
{
	for (auto iter : pObjectManager->objectList)
	{
		if (iter->type == _type)
		{
			iter->Die();
		}
	}
}

void ObjectManager::Update()
{
	for (auto iter : pObjectManager->objectList)
	{
		iter->Update();
	}
}

void ObjectManager::LateUpdate()
{
	// 삭제
	auto& objList = pObjectManager->objectList;
	auto iter = objList.begin();
	auto end = objList.end();
	GameObject* target = nullptr;
	for (; iter != end;)
	{
		target = *iter;
		if (target->isDead)
		{
			delete target;
			iter = objList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	
	// 충돌
	
	auto citer = objList.begin();
	auto cend = objList.end();
	for (; citer != cend; ++citer)
	{
		auto citer2 = citer;
		++citer2;
		for (; citer2 != cend; ++citer2)
		{
			Character* target = dynamic_cast<Character*>(*citer);
			if (target->Collision(*citer2))
			{
				if ((*citer)->handlerTable[(int)EventId::COLLISION_OBJ] != nullptr)
				{
					EventManager::Broadcast<CollisionEvent>(*citer, *citer2);
				}
				if ((*citer2)->handlerTable[(int)EventId::COLLISION_OBJ] != nullptr)
				{
					EventManager::Broadcast<CollisionEvent>(*citer2, *citer);
				}
			}
		}
	}
	
}

void ObjectManager::Render()
{
	for (auto iter : pObjectManager->objectList)
	{
		iter->Render();
	}

	TimeManager::RenderFPS();
	WCHAR wstr[8];
	wsprintf(wstr, L"%d", pObjectManager->objectList.size());
	RenderManager::DrawString(wstr, WINDOW_WIDTH - 100, 0);
}
