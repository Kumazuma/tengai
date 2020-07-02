#pragma once

enum class EventId {
	NONE,
	DIE_MONSTER,//���Ͱ� �׾��� �� �߻��ؾ� �ϴ� �̺�Ʈ
	PASS_TIME,//��� �ð��� ������ �� �߻��ؾ� �ϴ� �̺�Ʈ
	COLLISION_OBJ,//�ٸ� ���Ϳ� �ε����� �� �߻��ؾ� �ϴ� �̺�Ʈ
	DIE_PLAYER,
	END
};
class Event {
public:
	Event(EventId _id) :id{ _id } {}
	virtual ~Event() = default;
	EventId id;
};
class GameObject;
class MonsterDiedEvent : public Event
{
public:
	MonsterDiedEvent(const GameObject* _monster) :
		Event{ EventId::DIE_MONSTER },
		monster{ _monster }
	{

	}
	const GameObject* monster;
};
class TimePassedEvent : public Event
{
public:
	TimePassedEvent(const float _time) :
		Event{ EventId::PASS_TIME },
		time{ _time }
	{

	}
	const float time;
};
class CollisionEvent : public Event
{
public:
	CollisionEvent(const GameObject* _other) :
		Event{ EventId::COLLISION_OBJ },
		other{ _other }
	{

	}
	const GameObject* other;
};
