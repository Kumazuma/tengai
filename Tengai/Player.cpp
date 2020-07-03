#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "CharacterState.h"
#include "item.h"
#include <type_traits>
Player::Player()
{
	position = { 50, 50 };
	speed = 250;
	width = 30;
	height = 30;
	hp = 3;
	type = ObjectType::PLAYER;
	simpleCollider = { -15,-15,15,15 };
	pFireState = new PlayerAdditionalAttackState{ this, 0.15f };
	colliders.push_back(simpleCollider);
	Bind(EventId::COLLISION_OBJ, &Player::OnCollision);
}

Player::~Player()
{
	
}

void Player::Update()
{
	if (InputManager::GetKeyDown(VK_ESCAPE))
	{
		MainGame::Pause();
		return;
	}

	// 방향키
	if (InputManager::GetKey(VK_LEFT))
	{
		if (InputManager::GetKey(VK_UP))
		{
			Move(Direction::LEFT_UP);
		}
		else if(InputManager::GetKey(VK_DOWN))
		{
			Move(Direction::LEFT_DOWN);
		}
		else
		{
			Move(Direction::LEFT);
		}
	}
	else if (InputManager::GetKey(VK_RIGHT))
	{
		if (InputManager::GetKey(VK_UP))
		{
			Move(Direction::RIGHT_UP);
		}
		else if (InputManager::GetKey(VK_DOWN))
		{
			Move(Direction::RIGHT_DOWN);
		}
		else
		{
			Move(Direction::RIGHT);
		}
	}
	else if (InputManager::GetKey(VK_UP))
	{
		Move(Direction::UP);
	}
	else if (InputManager::GetKey(VK_DOWN))
	{
		Move(Direction::DOWN);
	}
	pFireState->Update();

}

void Player::Render()
{
	RenderManager::DrawSimpleCollider(simpleCollider + position, RGB(0, 200, 0));
}

void Player::OnCollision(const CollisionEvent& event)
{
	if (event.other->type == ObjectType::BULLET)
	{
		auto* pBullet = (Bullet*)event.other;
		if (pBullet->isAlias == false)
		{
			//나는 맞았다.
			--hp;
			if (hp <= 0)
			{
				Die();
			}
			else if(dynamic_cast<PlayerAdditionalAttackState*>(pFireState) != nullptr) {
				//맞으면 기본 무기로 돌아간다.
				auto current = pFireState->current;
				auto interval = pFireState->interval;
				auto tick = pFireState->tick;
				auto time = pFireState->time;
				delete pFireState;
				pFireState = new PlayerBasicAttackState{ this, interval, time };
				pFireState->current = current;
				pFireState->tick = tick;
			}
		}
	}
	else if (event.other->type == ObjectType::ITEM)
	{
		Item* pItem = (Item*)event.other;
		switch (pItem->itemType)
		{
		case ItemType::HEAL:
			hp += 1;
			break;
		case ItemType::SKILL:
		if(dynamic_cast<PlayerAdditionalAttackState*>(pFireState) == nullptr) {
			auto current = pFireState->current;
			auto interval = pFireState->interval;
			auto tick = pFireState->tick;
			auto time = pFireState->time;
			delete pFireState;
			pFireState = new PlayerAdditionalAttackState{ this, interval, time };
			pFireState->current = current;
			pFireState->tick = tick;
		}
			break;
		}
	}
}

void Player::Move(Direction _direction)
{
	float _speed = speed * TimeManager::DeltaTime();
	float _x = position.x;
	float _y = position.y;

	switch (_direction)
	{
	case Direction::UP:
		position.y -= _speed;
		break;
	case Direction::DOWN:
		position.y += _speed;
		break;
	case Direction::LEFT:
		position.x -= _speed;
		break;
	case Direction::RIGHT:
		position.x += _speed;
		break;
	case Direction::LEFT_UP:
		position.y -= _speed / sqrtf(2.f);
		position.x -= _speed / sqrtf(2.f);
		break;
	case Direction::LEFT_DOWN:
		position.y += _speed / sqrtf(2.f);
		position.x -= _speed / sqrtf(2.f);
		break;
	case Direction::RIGHT_UP:
		position.y -= _speed / sqrtf(2.f);
		position.x += _speed / sqrtf(2.f);
		break;
	case Direction::RIGHT_DOWN:
		position.y += _speed / sqrtf(2.f);
		position.x += _speed / sqrtf(2.f);
		break;
	default:
		break;
	}


	if (position.x <= 0 || position.x >= WINDOW_WIDTH)
	{
		position.x = _x;
	}
	if (position.y <= 0 || position.y >= WINDOW_HEIGHT)
	{
		position.y = _y;
	}
}
void Player::Die()
{
	GameObject::Die();
	//TODO:임시처리
	MainGame::Pause();
}
