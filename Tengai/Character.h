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
	RECT simpleCollider; // ��ü�� ���δ� Ŀ�ٶ� �簢����
	vector<RECT> colliders; // ���� �浹����
	int hp = 0;
};
