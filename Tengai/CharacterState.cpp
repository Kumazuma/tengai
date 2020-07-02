#include "stdafx.h"
#include "CharacterState.h"
BezierCurveMoveToState::BezierCurveMoveToState(Character* const _pCharacter, const Transform& _start, const Transform& _center, const Transform& _dest) :
	MoveToState{ _pCharacter, _start, _dest }, center{ _center }
{

}
ICharacterState* BezierCurveMoveToState::Update()
{

	Transform _monsterPos{ pCharacter->position.x, pCharacter->position.y };
	const float _speed = pCharacter->speed / 10.f;
	for (int i = 0; i < 10; ++i)
	{
		//���α׷����� 1�� �ǰų�, ���������� ����������
		if (progress >= 0.75f && (destination - _monsterPos).Length() < _speed)
		{
			pCharacter->position.x = destination.x;
			pCharacter->position.y = destination.y;
			//�̸� ������ ���� ���� ��ȯ�Ѵ�.
			return pNextState;
		}
		//���� ��ġ���� �����ϸ�, ���� ��ġ�� ����Ѵ�.
		if ((next - _monsterPos).Length() < _speed)
		{
			_monsterPos = next;
			progress += 0.001;
			float restTime = 1.f - progress;
			//2�� ������ ��� ���� ���
			next =
				restTime * (restTime * start + progress * center) //(1-t){(1-t)A + tB}
				+ progress * (restTime * center + progress * destination);//+t{(1-t)B + tC}
		}
		//���Ϳ� ���� ������ �մ� ������ �������� �ϴ� �ﰢ���� ������ ���ϰ�, 
		Transform relativeNextPos = next - _monsterPos;
		float radian = atan2(relativeNextPos.y, relativeNextPos.x);
		Matrix mat = Matrix::Rotate(radian) * Matrix::Translate(_speed, 0);
		//�ش� ������ speed��ŭ �̵��Ѵ�.
		_monsterPos += (Transform)mat;
	}
	pCharacter->position.x = _monsterPos.x;
	pCharacter->position.y = _monsterPos.y;

	return this;
}

void BezierCurveMoveToState::Reset()
{
	MoveToState::Reset();
	next = start;
}

WaitState::WaitState(int _tick) :
	tick{ _tick }, now{ 0 }, pNextState{ nullptr }
{

}

void WaitState::Reset()
{
	now = 0;
}

ICharacterState* WaitState::Update()
{
	if (tick == now)
	{
		return pNextState;
	}
	++now;
	return this;
}

MoveToState::MoveToState(Character* const _pCharecter, const Transform& _start, const Transform& _dest) :
	pCharacter{ _pCharecter }, progress {0.f}, start{ _start }, destination{ _dest }, pNextState{ nullptr }
{
}

void MoveToState::Reset()
{
	progress = 0.0f;
}

LinearMoveToState::LinearMoveToState(Character* const _pCharecter, const Transform& _start, const Transform& _dest) :
	MoveToState{ _pCharecter, _start, _dest }
{
}

ICharacterState* LinearMoveToState::Update()
{
	Transform _monsterPos{ pCharacter->position.x, pCharacter->position.y };
	const float _speed = pCharacter->speed / 10.f;
	for (int i = 0; i < 10; ++i)
	{
		//���α׷����� 1�� �ǰų�, ���������� ����������
		if (progress >= 0.75f && (destination - _monsterPos).Length() < _speed)
		{
			pCharacter->position.x = destination.x;
			pCharacter->position.y = destination.y;
			//�̸� ������ ���� ���� ��ȯ�Ѵ�.
			return pNextState;
		}
		//���Ϳ� ���� ������ �մ� ������ �������� �ϴ� �ﰢ���� ������ ���ϰ�, 
		Transform relativeNextPos = destination - _monsterPos;
		float radian = atan2(relativeNextPos.y, relativeNextPos.x);
		Matrix mat = Matrix::Rotate(radian) * Matrix::Translate(_speed, 0);
		//�ش� ������ speed��ŭ �̵��Ѵ�.
		_monsterPos += (Transform)mat;
	}
	pCharacter->position.x = _monsterPos.x;
	pCharacter->position.y = _monsterPos.y;
	return this;
}
