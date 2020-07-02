#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	position = { 100, 100 };
	speed = 5;
	width = 100;
	height = 100;
	Bind(EventId::COLLISION_OBJ, &Player::OnCollision);
}

Player::~Player()
{
	
}

void Player::Update()
{
	if (InputManager::GetKey(VK_UP))
	{
		position.y -= speed;
	}
	if (InputManager::GetKey(VK_DOWN))
	{
		position.y += speed;
	}
	if (InputManager::GetKey(VK_LEFT))
	{
		position.x -= speed;
	}
	if (InputManager::GetKey(VK_RIGHT))
	{
		position.x += speed;
	}

}

void Player::Render()
{
	RenderManager::DrawRect(RECT{ 0,0 ,width,height } + position);
}
#include "Bullet.h"
void Player::OnCollision(const CollisionEvent& event)
{
	if (event.other->type == ObjectType::BULLET)
	{
		auto* pBullet = (Bullet*)event.other;
		if (pBullet->isAlias == false)
		{
			//나는 맞았다.
			--hp;
			if (hp == 0)
			{
				Die();
				
			}
		}
	}
}
