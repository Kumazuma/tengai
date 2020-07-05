#include "stdafx.h"
#include "CharacterState.h"
#include "TimeManager.h"
#include "Bullet.h"
BezierCurveMoveToState::BezierCurveMoveToState(Character* const _pCharacter, const Transform& _start, const Transform& _center, const Transform& _dest) :
	MoveToState{ _pCharacter, _start, _dest }, center{ _center }
{

}
bool BezierCurveMoveToState::Update()
{
	const float _speed =TimeManager::DeltaTime()* pCharacter->speed / 10.f;
	for (int i = 0; i < 10; ++i)
	{
		//프로그래스가 1이 되거나, 목적지까지 도달했으면
		if (progress >= 0.75f && (destination - pCharacter->position).Length() < _speed)
		{
			pCharacter->position = destination;
			//미리 지정된 다음 씬을 반환한다.
			return true;
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
	return false;
}

void BezierCurveMoveToState::Reset()
{
	MoveToState::Reset();
	next = start;
}

WaitState::WaitState(float _time) :
	time{ _time }, current{ 0 }
{

}

void WaitState::Reset()
{
	current = 0;
}

bool WaitState::Update()
{
	if (current >= time)
	{
		return true;
	}
	current += TimeManager::DeltaTime();
	return false;
}

MoveToState::MoveToState(Character* const _pCharecter, const Transform& _start, const Transform& _dest) :
	pCharacter{ _pCharecter }, progress {0.f}, start{ _start }, destination{ _dest }
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

bool LinearMoveToState::Update()
{
	
	const float _speed = TimeManager::DeltaTime() * pCharacter->speed / 10.f;
	for (int i = 0; i < 10; ++i)
	{
		//프로그래스가 1이 되거나, 목적지까지 도달했으면
		if (progress >= 0.75f && (destination - pCharacter->position).Length() < _speed)
		{
			pCharacter->position = destination;
			//미리 지정된 다음 씬을 반환한다.
			return true;
		}
		//몬스터와 다음 점까지 잇는 선분을 빗변으로 하는 삼각형의 각도를 구하고, 
		Transform relativeNextPos = destination - pCharacter->position;
		float radian = atan2(relativeNextPos.y, relativeNextPos.x);
		Matrix mat = Matrix::Rotate(radian) * Matrix::Translate(_speed, 0);
		//해당 각도로 speed만큼 이동한다.
		pCharacter->position += (Transform)mat;
	}
	return false;
}

FocusOnPlayerFireState::FocusOnPlayerFireState(Character* _pCharacter, float _interval,  float _time):
	FireState{ _pCharacter, _interval,  _time }
{

}

bool FocusOnPlayerFireState::Update()
{
	if (tick >= interval)
	{
		//사격
		const Character* const pPlayer = (Character*) ObjectManager::GetInstance()->pPlayer;
		if (pPlayer == nullptr)
		{
			return FireState::Update();
		}
		const Transform dpos = pPlayer->position - pCharacter->position;

		const float radian = atan2f(dpos.y, dpos.x);
		GameObject* bullet = ObjectManager::CreateObject(ObjectType::BULLET);
		MetaBullet::Initialize(bullet, BulletType::_01, pCharacter->position , radian, false);
		tick -= interval;
	}
	return FireState::Update();
}


FireState::FireState(Character* pCharacter, float _interval, float _time):
	pCharacter{ pCharacter }, interval{ _interval }, tick{ 0.f }, current{_time}, time{_time}
{
}

bool FireState::Update()
{
	auto delta = TimeManager::DeltaTime();
	if (current <= delta)
	{
		return true;
	}
	current -= delta;
	tick += delta;
	return false;
}

void FireState::Reset()
{
	tick = 0.f;
	current = time;
}

FlowerFireState::FlowerFireState(Character* pCharacter, float _interval, float _time):
	FireState{ pCharacter, _interval, _time }
{
}

bool FlowerFireState::Update()
{
	if (tick >= interval)
	{
		Transform leftTop{ (float)pCharacter->simpleCollider.left, (float)pCharacter->simpleCollider.top };
		float length = leftTop.Length();
		auto move = Matrix::Translate(length, 0);
		const Transform& center = pCharacter->position;
		constexpr int BULLET_COUNT = 22;
		//사격
		for (int i = 0; i < BULLET_COUNT; ++i)
		{
			const float radian = PI * i * (360 / BULLET_COUNT) / 180;
			Transform pos = static_cast<Transform>(Matrix::Translate(center.x, center.y) * Matrix::Rotate(radian) * move);
			GameObject* bullet = ObjectManager::CreateObject(ObjectType::BULLET);
			MetaBullet::Initialize(bullet, BulletType::_03, pos, radian, false);
		}
		tick -= interval;
	}
	return FireState::Update();
}

FlowerCurvesFireState::FlowerCurvesFireState(Character* pCharacter, float _interval,  float _time):
	FireState{ pCharacter, _interval , _time }
{
}

bool FlowerCurvesFireState::Update()
{
	if (tick >= interval)
	{
		Transform leftTop{ (float)pCharacter->simpleCollider.left, (float)pCharacter->simpleCollider.top };
		float length = leftTop.Length();
		auto move = Matrix::Translate(length, 0);
		const Transform& center = pCharacter->position;
		constexpr int BULLET_COUNT = 22;
		//사격
		for (int i = 0; i < BULLET_COUNT; ++i)
		{
			const float radian = PI * i * (360 / BULLET_COUNT) / 180;
			Transform pos = static_cast<Transform>(Matrix::Translate(center.x, center.y) * Matrix::Rotate(radian) * move);
			GameObject* bullet = ObjectManager::CreateObject(ObjectType::BULLET);
			MetaBullet::Initialize(bullet, BulletType::_02, pos, radian, false);
		}
		tick -= interval;
	}
	return FireState::Update();
}

DeleteState::DeleteState(Character* const _pCharacter):
	pCharacter{ _pCharacter }
{

}

bool DeleteState::Update()
{
	pCharacter->Die();
	return false;
}

void DeleteState::Reset()
{
}

CharacterState::CharacterState():
	pNextState{nullptr}
{
}

PlayerBasicAttackState::PlayerBasicAttackState(Character* pCharacter, float _interval, float _time):
	FireState{pCharacter, _interval, _time}
{

}


PlayerAdditionalAttackState::PlayerAdditionalAttackState(Character* pCharacter, float _interval, float _time):
	PlayerBasicAttackState{ pCharacter, _interval, _time }
{
	
}
bool PlayerBasicAttackState::Update()
{

	// 공격키
	if (InputManager::GetKey('A'))
	{
		if (tick >= interval)
		{
			GameObject* bullet = ObjectManager::CreateObject(ObjectType::BULLET);
			MetaBullet::Initialize(bullet, BulletType::_04, pCharacter->position, 0, true);
			tick = 0;
		}
		
	}
	FireState::Update();
	return false;
}

bool PlayerAdditionalAttackState::Update()
{
	if (InputManager::GetKey('A'))
	{
		if (tick >= interval)
		{
			GameObject* bullet = ObjectManager::CreateObject(ObjectType::BULLET);
			MetaBullet::Initialize(bullet, BulletType::_05, pCharacter->position, 1.5f, true);
		}
	}
	PlayerBasicAttackState::Update();
	return false;
}
