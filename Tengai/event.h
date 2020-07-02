#pragma once

enum class EventId {
	NONE,
	DIE_MONSTER,//몬스터가 죽었을 때 발생해야 하는 이벤트
	PASS_TIME,//어느 시간이 지났을 때 발생해야 하는 이벤트
	COLLISION_OBJ,//다른 몬스터와 부딪쳤을 때 발생해야 하는 이벤트
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
