#pragma once
#include "Character.h"
#include "CharacterState.h"
#include <vector>
enum class MonsterType
{
	NONE = 0,
	MOB01,
	MOB02,
	BOSS,
	END
};

class Monster :
	public Character
{
	//method
public:
	Monster();
	void Initialize(MonsterType monsterType, const Transform& firstPos);
	~Monster();
	void Update() override;
	void Render() override;
	//variable
public:
	RECT monsterRect;
	MonsterType monsterType;
	CharacterState* currentFireState;
	CharacterState* currentMoveState;
	std::vector<CharacterState*> moveStateList;
	std::vector<CharacterState*> fireStateList;
};

