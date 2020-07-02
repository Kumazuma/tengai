#pragma once
#include "event.h"
#include "Define.h"
enum class ObjectType
{
	NONE,
	MONSTER,
	PLAYER,
	BULLET,
	UI,

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
	void Die();

	float x = 0.f;
	float y = 0.f;
	int width = 0;
	int height = 0;
	
	ObjectType type = ObjectType::NONE;
	bool isDead = false;
	int uid = 0;
	//�̺�Ʈ �ڵ鸵�� ���� �ڵ鷯 ���̺�� �� �Լ���...
	void HandleEvent(const Event& _event);
	template<typename _DerivedClass, typename _EventT>
	void Bind(EventId _id, void(_DerivedClass::* _handler)(const _EventT&));
	void _Bind(EventId _id, EventHandler _handler);
	EventHandler handlerTable[ENUM_MAX<EventId>()]{};
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
		//Ÿ�� �켱 ���� ����
		if (obj1->type != obj2->type)
		{
			return obj1->type < obj2->type;
		}
		//���� ������ ���� ����.
		return obj1->uid < obj2->uid;
	}
};
