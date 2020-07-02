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
		pObj = pObjectManager->bulletPool.Alloc();
		break;
	case ObjectType::UI:
		pObj = new UI();
		break;
	default:
		return nullptr;
	}

	pObj->uid = ++lastUid;
	pObjectManager->objectTable[(int)_type].push_back(pObj);
	pObjectManager->objectList.push_back(pObj);

	return pObj;
}

bool ObjectManager::DeleteObject(GameObject * _target)
{
	auto& objList = pObjectManager->objectTable[(int)_target->type];
	
	auto target = find(objList.begin(), objList.end(), _target);
	if (target != objList.end())
	{
		_target->Die();
		return true;
	}
	return false;
}

void ObjectManager::DestroyAll()
{
	auto& objTable = pObjectManager->objectTable;
	for (auto&objList  : objTable)
	{
		for (auto& iter : objList)
		{
			iter->Die();
		}
	}
}

void ObjectManager::DestroyAll(ObjectType _type)
{
	auto& objList = pObjectManager->objectTable[(int)_type];
	for (auto iter : objList)
	{
		iter->Die();
	}
}

void ObjectManager::Update()
{
	auto& objTable = pObjectManager->objectTable;
	for (auto& objList : objTable)
	{
		for (auto& iter : objList)
		{
			iter->Update();
		}
	}
	
}

void ObjectManager::LateUpdate()
{
	auto& objTable = pObjectManager->objectTable;
	auto& goList = pObjectManager->objectList;
	GameObject* target = nullptr;
	for (auto& objList : objTable)
	{
		auto iter = objList.begin();
		auto end = objList.end();
		for (;iter!=end;)
		{
			target = *iter;
			if (target->isDead)
			{
				auto findResult = find(goList.begin(), goList.end(), (*iter));
				goList.erase(findResult);
				iter = objList.erase(iter);

				if (target->type == ObjectType::BULLET)
				{
					pObjectManager->bulletPool.Free((Bullet*)target);
				}
				else
				{
					delete target;
				}
			}
			else
			{
				++iter;
			}
		}
	}
	
	// �浹
	
	auto citer = pObjectManager->objectList.begin();
	auto cend = pObjectManager->objectList.end();
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
	auto& objTable = pObjectManager->objectTable;
	for (auto& objList : objTable)
	{
		for (auto& iter : objList)
		{
			iter->Render();
		}
	}

	TimeManager::RenderFPS();
	WCHAR wstr[8];
	wsprintf(wstr, L"%d", pObjectManager->objectList.size());
	RenderManager::DrawString(wstr, WINDOW_WIDTH - 100, 0);
}
