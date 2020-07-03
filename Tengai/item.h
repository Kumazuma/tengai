#pragma once
#include"stdafx.h"
#include<Windows.h>
#include<vector>
#include "Character.h"
#include "CharacterState.h"
enum class ItemType
{
	NONE,
	HEAL,//먹으면 체력 1회복
	SKILL,//먹으면 추가 공격 패턴을 얻음
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
	void OnCollision(const CollisionEvent& event);
	void MakeNewDest();
	const ItemType itemType;
	MoveToState* pState;
};
class HealItem : public Item
{
public:
	HealItem(ItemType _type, const Transform& pos);
	virtual ~HealItem();
	virtual void Render() override;
};
class SkillItem : public Item
{
public:
	SkillItem(ItemType _type, const Transform& pos);
	virtual ~SkillItem();
	virtual void Render() override;
};