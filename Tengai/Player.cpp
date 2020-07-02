#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	position = { 100, 100 };
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
