#pragma once
#include "Transform.h"
#include "Character.h"
//캐릭터의 상태, 이동 과 총알 발사 처리를 대행한다.
struct CharacterState
{
	CharacterState();
	virtual bool Update() = 0;
	virtual void Reset() = 0;
	virtual ~CharacterState() = default;
	CharacterState* pNextState;
};
class MoveToState :public CharacterState
{
public:
	MoveToState(Character* const _pCharecter, const Transform& _start, const Transform& _dest);
	void Reset() override;
	float progress;/*[0 - 1]*/
	Character* pCharacter;
	Transform destination;
	Transform start;
};
//특정한 위치를 직선으로 이동한다.
class LinearMoveToState : public MoveToState
{
public:
	LinearMoveToState(Character* const _pCharecter, const Transform& _start, const Transform& _dest);
	bool Update() override;
};
//특정한 위치를 베지어 곡선을 이용하여 이동한다.
class BezierCurveMoveToState :public MoveToState
{
public:
	BezierCurveMoveToState(Character* const _pCharecter, const Transform& _start, const Transform& _center, const Transform& _dest);
	bool Update() override;
	void Reset() override;
	Transform center;
	Transform next;
};
class DeleteState : public CharacterState
{
public:
	DeleteState(Character* const _pCharacter);
	bool Update() override;
	void Reset() override;
	Character* const pCharacter;
};
//해당 위치에 대기하는 상태
class WaitState :public CharacterState
{
public:

	//-1은 infinite
	WaitState(float _time);
	void Reset() override;
	bool Update() override;
	float time;
	float current;
};
class FireState: public CharacterState
{
public:
	FireState(Character* pCharacter, float _interval,  float _time = 9999.f);
	bool Update() override;
	void Reset() override;
	Character* pCharacter;
	float tick;
	const float interval;
	const float time;
	float current;
};
//주인공의 있는 방향으로 총발을 발사하는 비헤이비어
class FocusOnPlayerFireState : public FireState
{
public:
	FocusOnPlayerFireState(Character* pCharacter, float _interval, float _time = 9999.f);
	bool Update() override;
};
//방사형으로 쏘는 함수
class FlowerFireState : public FireState
{
public:
	FlowerFireState(Character* pCharacter, float _interval, float _time = 9999.f);
	bool Update() override;
};
//방사형으로 조금씩 도는 총알을 쏘는 함수
class FlowerCurvesFireState : public FireState
{
public:
	FlowerCurvesFireState(Character* pCharacter, float _interval, float _time = 9999.f);
	bool Update() override;
};
//플레이어의 기본 공격
class PlayerBasicAttackState : public FireState
{
public:
	PlayerBasicAttackState(Character* pCharacter, float _interval, float _time = 9999.f);
	bool Update() override;
};
class PlayerAdditionalAttackState : public PlayerBasicAttackState
{
public:
	PlayerAdditionalAttackState(Character* pCharacter, float _interval, float _time = 9999.f);
	bool Update() override;
};