#pragma once

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
};

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
