#pragma once
#include "Character.h"
#include "CharacterState.h"
enum MonsterType
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
	~Monster() = default;
	void Update() override;
	void Render() override;
	//variable
public:
	MonsterType monsterType;
	ICharacterState* pState;
	BezierCurveMoveToState initState;
	WaitState waitState;
	BezierCurveMoveToState moveUpState;
	WaitState waitState2;
	BezierCurveMoveToState moveDownState;
	FlowerFireState fireState;
};

