#include "stdafx.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"
#include "UI.h"
#include "Bullet.h"
#include "PauseBox.h"
#include "BackGround.h"
#include "item.h"
#include "GameOverBox.h"
#include "TitleUI.h"
ObjectManager* pObjectManager = nullptr;
int lastUid = 0;

ObjectManager::ObjectManager()
{
	pBG = BackGround::GetInstance();

	pBG->uid = ++lastUid;
}

ObjectManager::~ObjectManager()
{
	BackGround::Release();
	for (auto it : pObjectManager->objectList)
	{
		if (it->type != ObjectType::BULLET)
		{
			delete it;
		}
		else
		{
			this->bulletPool.Free((Bullet*)it);
		}
		
	}
	pObjectManager->objectList.clear();
}

void ObjectManager::AddObject(ObjectType _type, GameObject* pObj)
{
	pObj->uid = ++lastUid;
	pObjectManager->objectTable[(int)_type].push_back(pObj);
	pObjectManager->objectList.push_back(pObj);
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
	case ObjectType::ITEM:
		pObj = new Item{};
		break;
	case ObjectType::UI:
		pObj = new UI();
		break;
	case ObjectType::TITLE_UI:
		pObj = new TitleUI;
		break;
	case ObjectType::PRESSKEY_UI:
		pObj = new PressAnyKeyUI();
		break;
	default:
		return nullptr;
	}

	pObj->type = _type;
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

void ObjectManager::Release()
{
	delete pObjectManager;
	pObjectManager = nullptr;
}

void ObjectManager::Update()
{
	BackGround::GetInstance()->Update();

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
				if (target == pObjectManager->pPlayer)
				{
					pObjectManager->pPlayer = nullptr;
				}
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
	
	// 충돌
	
	auto citer = pObjectManager->objectList.begin();
	auto cend = pObjectManager->objectList.end();
	for (; citer != cend; ++citer)
	{
		Character* target = dynamic_cast<Character*>(*citer);
		if (target == nullptr)
		{
			continue;
		}
		auto citer2 = citer;
		++citer2;
		for (; citer2 != cend; ++citer2)
		{
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
	// 백그라운드 (최하위)
	BackGround::GetInstance()->Render();

	auto& objTable = pObjectManager->objectTable;
	for (auto& objList : objTable)
	{
		for (auto& iter : objList)
		{
			iter->Render();
		}
	}

	// 디버그용
	TimeManager::RenderFPS();
	ObjectManager::RenderBulletCount();
	ObjectManager::RenderHP();

	// 퍼즈박스 (최상위 렌더)
}

void ObjectManager::RenderBulletCount()
{
	auto& bulletList = pObjectManager->objectTable[(int)ObjectType::BULLET];
	WCHAR wstr[32] = {};
	wsprintf(wstr, L"BulletCount : %d", (int)bulletList.size());
	RenderManager::DrawString(wstr, WINDOW_WIDTH - 130, 0);
}

void ObjectManager::RenderHP()
{
	if (pObjectManager->pPlayer == nullptr) return;
	WCHAR wText[64] = {};
	wsprintf(wText, L"HP : %d", pObjectManager->pPlayer->hp);
	RenderManager::DrawString(wText, 130, 0);
}
