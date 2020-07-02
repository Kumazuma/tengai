#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	x = 100;
	y = 100;
	speed = 5;
	width = 100;
	height = 100;
}

Player::~Player()
{
}

void Player::Update()
{
	if (InputManager::GetKey(VK_UP))
	{
		y -= speed;
	}
	if (InputManager::GetKey(VK_DOWN))
	{
		y += speed;
	}
	if (InputManager::GetKey(VK_LEFT))
	{
		x -= speed;
	}
	if (InputManager::GetKey(VK_RIGHT))
	{
		x += speed;
	}

}

void Player::Render()
{
	RenderManager::DrawRect({ (int)x,(int)y,(int)x + width,(int)y + height });
}
