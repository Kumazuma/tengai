#pragma once
#include"stdafx.h"
#include<Windows.h>
#include<vector>
#include "Character.h"
enum class ItemType
{
	NONE,
	HEAL,//������ ü�� 1ȸ��
	POINT,//������ ������ ����
	END
};
class Item : public Character
{
public:
	Item();
	Item(ItemType _type, const Transform& pos);
	static GameObject* Initialize(GameObject* const obj, ItemType _type, const Transform& pos);
	virtual ~Item();
	virtual void Update() override;
	virtual void Render() override;
	void OnCollision(const CollisionEvent& event);
	const ItemType itemType;
};