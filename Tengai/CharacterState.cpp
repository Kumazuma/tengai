#include "stdafx.h"
#include "CharacterState.h"
#include "TimeManager.h"
#include "Bullet.h"
BezierCurveMoveToState::BezierCurveMoveToState(Character* const _pCharacter, const Transform& _start, const Transform& _center, const Transform& _dest) :
	MoveToState{ _pCharacter, _start, _dest }, center{ _center }
{

}
ICharacterState* BezierCurveMoveToState::Update()
{
	const float _speed = pCharacter->speed / 10.f;
	for (int i = 0; i < 10; ++i)
	{
		//프로그래스가 1이 되거나, 목적지까지 도달했으면
		if (progress >= 0.75f && (destination - pCharacter->position).Length() < _speed)
		{
			pCharacter->position = destination;
			//미리 지정된 다음 씬을 반환한다.
			return pNextState;
		}
		//다음 위치까지 도착하면, 다음 위치를 계산한다.
		if ((next - pCharacter->position).Length() < _speed)
		{
			pCharacter->position = next;
			progress += 0.001f;
			float restTime = 1.f - progress;
			//2차 베지에 곡선의 수직 계산
			next =
				restTime * (restTime * start + progress * center) //(1-t){(1-t)A + tB}
				+ progress * (restTime * center + progress * destination);//+t{(1-t)B + tC}
		}
		//몬스터와 다음 점까지 잇는 선분을 빗변으로 하는 삼각형의 각도를 구하고, 
		Transform relativeNextPos = next - pCharacter->position;
		float radian = atan2(relativeNextPos.y, relativeNextPos.x);
		Matrix mat = Matrix::Rotate(radian) * Matrix::Translate(_speed, 0);
		//해당 각도로 speed만큼 이동한다.
		pCharacter->position += (Transform)mat;
	}
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
	
	const float _speed = pCharacter->speed / 10.f;
	for (int i = 0; i < 10; ++i)
	{
		//프로그래스가 1이 되거나, 목적지까지 도달했으면
		if (progress >= 0.75f && (destination - pCharacter->position).Length() < _speed)
		{
			pCharacter->position = destination;
			//미리 지정된 다음 씬을 반환한다.
			return pNextState;
		}
		//몬스터와 다음 점까지 잇는 선분을 빗변으로 하는 삼각형의 각도를 구하고, 
		Transform relativeNextPos = destination - pCharacter->position;
		float radian = atan2(relativeNextPos.y, relativeNextPos.x);
		Matrix mat = Matrix::Rotate(radian) * Matrix::Translate(_speed, 0);
		//해당 각도로 speed만큼 이동한다.
		pCharacter->position += (Transform)mat;
	}
	return this;
}

FocusOnPlayerFireState::FocusOnPlayerFireState(Character* _pCharacter, float _interval):
	FireState{_pCharacter, _interval}
{
}

ICharacterState* FocusOnPlayerFireState::Update()
{
	if (tick >= interval)
	{
		//사격
		const Character* const pPlayer = (Character*) ObjectManager::GetInstance()->pPlayer;
		const Transform dpos = pPlayer->position - pCharacter->position;

		const float radian = atan2f(dpos.y, dpos.x);
		GameObject* bullet = ObjectManager::CreateObject(ObjectType::BULLET);
		MetaBullet::Initialize(bullet, BulletType::_01, pCharacter->position , radian, false);
		tick -= interval;
	}
	tick += TimeManager::DeltaTime();
	return this;
}

FireState::FireState(Character* pCharacter, float _interval):
	pCharacter{pCharacter}, interval{_interval}, tick{0.f}
{
	tick = 0;
}

void FireState::Reset()
{

}

FlowerFireState::FlowerFireState(Character* pCharacter, float _interval):
	FireState{ pCharacter, _interval }
{
}

ICharacterState* FlowerFireState::Update()
{
	if (tick >= interval)
	{
		//사격
		for (int i = 0; i < 45; ++i)
		{
			const float radian = 3.141592f * i * 8.f / 180;
			GameObject* bullet = ObjectManager::CreateObject(ObjectType::BULLET);
			MetaBullet::Initialize(bullet, BulletType::_01, pCharacter->position, radian, false);
		}
		tick -= interval;
	}
	tick += TimeManager::DeltaTime();
	return this;
}
