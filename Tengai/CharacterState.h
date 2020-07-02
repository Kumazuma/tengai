#pragma once
#include "Transform.h"
#include "Character.h"
//ĳ������ ����, �̵� �� �Ѿ� �߻� ó���� �����Ѵ�.
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
//Ư���� ��ġ�� �������� �̵��Ѵ�.
class LinearMoveToState : public MoveToState
{
public:
	LinearMoveToState(Character* const _pCharecter, const Transform& _start, const Transform& _dest);
	ICharacterState* Update() override;
};
//Ư���� ��ġ�� ������ ��� �̿��Ͽ� �̵��Ѵ�.
class BezierCurveMoveToState :public MoveToState
{
public:
	BezierCurveMoveToState(Character* const _pCharecter, const Transform& _start, const Transform& _center, const Transform& _dest);
	ICharacterState* Update() override;
	void Reset() override;
	Transform center;
	Transform next;
};
//�ش� ��ġ�� ����ϴ� ����
class WaitState :public ICharacterState
{
public:
	WaitState(int _tick);
	void Reset() override;
	ICharacterState* Update() override;
	int tick;
	int now;
	ICharacterState* pNextState;
};