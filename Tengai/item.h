#pragma once
#include"stdafx.h"
#include<Windows.h>
#include<vector>
#include "Character.h"
enum class ItemType
{
	NONE,
	HEAL,//먹으면 체력 1회복
	POINT,//먹으면 점수를 얻음
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