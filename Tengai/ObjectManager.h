#pragma once
#include <list>
#include "GameObject.h"
#include "Bullet.h"

using namespace std;

class Player;

class ObjectManager
{
private:
	ObjectManager();
	~ObjectManager();

public:
	static ObjectManager* GetInstance();
	static GameObject* CreateObject(ObjectType _type);
	static bool DeleteObject(GameObject* _target);
	static void DestroyAll();
	static void DestroyAll(ObjectType _type);

	static void Update();
	static void LateUpdate();
	static void Render();

	static void RenderBulletCount();
	
	Player* pPlayer = nullptr;
	list<GameObject*>objectTable[ENUM_MAX<ObjectType>()];
	list<GameObject*>objectList;
	MemoryPool<Bullet> bulletPool;
};

