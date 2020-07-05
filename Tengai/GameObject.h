#pragma once
#include "event.h"
#include "Define.h"
#include "Transform.h"
enum class ObjectType
{
	NONE,
	MONSTER,
	PLAYER,
	BULLET,
	ITEM,
	UI,
	TITLE_UI,
	PRESSKEY_UI,

	END
};



class GameObject
{
public:
	typedef void(GameObject::* EventHandler)(const Event&);
public:
	GameObject();
	virtual ~GameObject();


	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void OnCollision(const GameObject& _other) {};
	virtual void Die();

	Transform position{ 0.f, 0.f };
	int width = 0;
	int height = 0;
	
	ObjectType type = ObjectType::NONE;
	bool isDead = false;
	int uid = 0;
	bool isEnable = true;
	bool isVisible = true;
	//이벤트 핸들링을 위한 핸들러 테이블과 그 함수들...
	void HandleEvent(const Event& _event);
	template<typename _DerivedClass, typename _EventT>
	void Bind(EventId _id, void(_DerivedClass::* _handler)(const _EventT&));
	void _Bind(EventId _id, EventHandler _handler);
	EventHandler handlerTable[ENUM_MAX<EventId>()]{};
	std::vector<Event*> eventQueue;
};
template<typename _DerivedClass, typename _EventT>
void GameObject::Bind(EventId _id, void(_DerivedClass::* _handler)(const _EventT&))
{
	static_assert(
		std::is_base_of<GameObject, _DerivedClass>::value == true,
		"_DerivedClass is not base of GameObject");
	static_assert(
		std::is_base_of<Event, _EventT>::value == true,
		"_EventT is not base of Event");
	_Bind(_id, (EventHandler)_handler);
}
class ObjectCompare
{
public:
	bool operator ()(const GameObject* obj1, const GameObject* obj2) const
	{
		//타입 우선 순위 먼저
		if (obj1->type != obj2->type)
		{
			return obj1->type < obj2->type;
		}
		//먼저 생성된 순위 먼저.
		return obj1->uid < obj2->uid;
	}
};
inline RECT CreateSimpleCollider(const std::vector<RECT>& colliders)
{
	RECT res{ 0,0,0,0 };
	for (const RECT& rc : colliders)
	{
		res.left = (res.left > rc.left) ? rc.left : res.left;
		res.top = (res.top > rc.top) ? rc.top : res.top;
		res.right = (res.right < rc.right) ? rc.right : res.right;
		res.bottom = (res.bottom < rc.bottom) ? rc.bottom : res.bottom;
	}
	return res;
}