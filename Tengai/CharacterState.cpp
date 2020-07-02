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
		//프로그래스가 1이 되거나, 목적지까지 도달했으면
		if (progress >= 0.75f && (destination - _monsterPos).Length() < _speed)
		{
			pCharacter->position.x = destination.x;
			pCharacter->position.y = destination.y;
			//미리 지정된 다음 씬을 반환한다.
			return pNextState;
		}
		//다음 위치까지 도착하면, 다음 위치를 계산한다.
		if ((next - _monsterPos).Length() < _speed)
		{
			_monsterPos = next;
			progress += 0.001;
			float restTime = 1.f - progress;
			//2차 베지에 곡선의 수직 계산
			next =
				restTime * (restTime * start + progress * center) //(1-t){(1-t)A + tB}
				+ progress * (restTime * center + progress * destination);//+t{(1-t)B + tC}
		}
		//몬스터와 다음 점까지 잇는 선분을 빗변으로 하는 삼각형의 각도를 구하고, 
		Transform relativeNextPos = next - _monsterPos;
		float radian = atan2(relativeNextPos.y, relativeNextPos.x);
		Matrix mat = Matrix::Rotate(radian) * Matrix::Translate(_speed, 0);
		//해당 각도로 speed만큼 이동한다.
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
		//프로그래스가 1이 되거나, 목적지까지 도달했으면
		if (progress >= 0.75f && (destination - _monsterPos).Length() < _speed)
		{
			pCharacter->position.x = destination.x;
			pCharacter->position.y = destination.y;
			//미리 지정된 다음 씬을 반환한다.
			return pNextState;
		}
		//몬스터와 다음 점까지 잇는 선분을 빗변으로 하는 삼각형의 각도를 구하고, 
		Transform relativeNextPos = destination - _monsterPos;
		float radian = atan2(relativeNextPos.y, relativeNextPos.x);
		Matrix mat = Matrix::Rotate(radian) * Matrix::Translate(_speed, 0);
		//해당 각도로 speed만큼 이동한다.
		_monsterPos += (Transform)mat;
	}
	pCharacter->position.x = _monsterPos.x;
	pCharacter->position.y = _monsterPos.y;
	return this;
}
