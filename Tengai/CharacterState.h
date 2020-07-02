#pragma once
#include "Transform.h"
#include "Character.h"
//캐릭터의 상태, 이동 과 총알 발사 처리를 대행한다.
struct ICharacterState
{
	virtual ICharacterState* Update() = 0;
	virtual void Reset() = 0;
	virtual ~ICharacterState() = default;
};
class MoveToState :public ICharacterState
{
public:
	MoveToState(Character* const _pCharecter, const Transform& _start, const Transform& _dest);
	void Reset() override;
	float progress;/*[0 - 1]*/
	Character* pCharacter;
	Transform destination;
	Transform start;

	ICharacterState* pNextState;
};
//특정한 위치를 직선으로 이동한다.
class LinearMoveToState : public MoveToState
{
public:
	LinearMoveToState(Character* const _pCharecter, const Transform& _start, const Transform& _dest);
	ICharacterState* Update() override;
};
//특정한 위치를 베지어 곡선을 이용하여 이동한다.
class BezierCurveMoveToState :public MoveToState
{
public:
	BezierCurveMoveToState(Character* const _pCharecter, const Transform& _start, const Transform& _center, const Transform& _dest);
	ICharacterState* Update() override;
	void Reset() override;
	Transform center;
	Transform next;
};

//해당 위치에 대기하는 상태
class WaitState :public ICharacterState
{
public:

	//-1은 infinite
	WaitState(int _tick);
	void Reset() override;
	ICharacterState* Update() override;
	int tick;
	int now;
	ICharacterState* pNextState;
};
class FireState: public ICharacterState
{
public:
	FireState(Character* pCharacter, float _interval);
	void Reset() override;
	Character* pCharacter;
	float tick;
	const float interval;
};
//주인공의 있는 방향으로 총발을 발사하는 비헤이비어
class FocusOnPlayerFireState : public FireState
{
public:
	FocusOnPlayerFireState(Character* pCharacter, float _interval);
	ICharacterState* Update() override;
};
//방사형으로 쏘는 함수
class FlowerFireState : public FireState
{
public:
	FlowerFireState(Character* pCharacter, float _interval);
	ICharacterState* Update() override;
};
