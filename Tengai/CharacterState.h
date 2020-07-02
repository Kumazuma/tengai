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

	//-1�� infinite
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
//���ΰ��� �ִ� �������� �ѹ��� �߻��ϴ� �����̺��
class FocusOnPlayerFireState : public FireState
{
public:
	FocusOnPlayerFireState(Character* pCharacter, float _interval);
	ICharacterState* Update() override;
};
//��������� ��� �Լ�
class FlowerFireState : public FireState
{
public:
	FlowerFireState(Character* pCharacter, float _interval);
	ICharacterState* Update() override;
};
