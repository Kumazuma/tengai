#pragma once
#include "GameObject.h"
class Character : public GameObject
{
public:
	Character() = default;
	~Character() = default;

	virtual void Update() override;
	virtual void Render() override;

	bool Collision(const GameObject* _target);

public:
	float speed = 0.f;
	RECT simpleCollider; // 객체를 감싸는 커다란 사각영역
	vector<RECT> colliders; // 실제 충돌영역
	int hp = 0;
};
