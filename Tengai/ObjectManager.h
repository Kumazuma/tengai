#pragma once
#include <list>
#include "GameObject.h"
#include "Bullet.h"

using namespace std;

class Player;
class PauseBox;
class BackGround;

class ObjectManager
{
private:
	ObjectManager();
	~ObjectManager();
	static void AddObject(ObjectType _type, GameObject*);
public:
	static ObjectManager* GetInstance();
	template<typename ObjT, typename ...Arg>
	static GameObject* CreateObject(ObjectType _type, Arg&& ...args);
	static GameObject* CreateObject(ObjectType _type);
	static bool DeleteObject(GameObject* _target);
	static void DestroyAll();
	static void DestroyAll(ObjectType _type);

	static void Release();
	static void Update();
	static void LateUpdate();
	static void Render();

	static void RenderBulletCount();
	static void RenderHP();
	
	Player* pPlayer = nullptr;
	PauseBox* pPauseUI = nullptr;
	BackGround* pBG = nullptr;

	list<GameObject*>objectTable[ENUM_MAX<ObjectType>()];
	list<GameObject*>objectList;
	MemoryPool<Bullet> bulletPool;
};

template<typename ObjT, typename ...Arg>
inline GameObject* ObjectManager::CreateObject(ObjectType _type, Arg&& ...args)
{
	GameObject* obj = new ObjT{ std::forward<Arg>(args)... };
	AddObject(_type, obj);
	return obj;
}
