#include "stdafx.h"
#include "Bullet.h"
#include "RenderManager.h"
#include "Transform.h"
#include <xmemory>
#include"GameObject.h"

Bullet::Bullet()
{
	type = ObjectType::BULLET;
	Bind(EventId::COLLISION_OBJ, &Bullet::OnCollision);
	simpleCollider = RECT{ -8,-8,8,8 };
}

void Bullet::Update()
{
	if (position.x <= 0 || position.y <= 0)
	{
		ObjectManager::DeleteObject(this);
	}
	if(position.x >= WINDOW_WIDTH || position.y >= WINDOW_HEIGHT)
	{ 
		ObjectManager::DeleteObject(this);
	}
}

void Bullet::Move()
{
	const float _speed = TimeManager::DeltaTime()* speed / 10.f;
	for (int i = 0; i < 10; ++i)
	{

		Matrix mat = Matrix::Rotate(radian) * Matrix::Translate(_speed, 0);
		//해당 각도로 speed만큼 이동한다.
		position += (Transform)mat;
	}
}

void Bullet::Render()
{
}

void Bullet::OnCollision(const CollisionEvent& event)
{
	if (event.other->type != ObjectType::BULLET)
	{
		if (event.other->type == ObjectType::MONSTER && this->isAlias == true)
		{
			ObjectManager::DeleteObject(this);
		}
		if (event.other->type == ObjectType::PLAYER && this->isAlias == false)
		{
			ObjectManager::DeleteObject(this);
		}
	}
}

void MetaBullet::Initialize(GameObject* _pObject, BulletType _type, const Transform& pos, float rad, bool _isAlias)
{
	if (_pObject == nullptr)
	{
		return;
	}
	if (_pObject->type != ObjectType::BULLET)
	{
		return;
	}
	Bullet* pBullet = (Bullet*)_pObject;
	auto uid = pBullet->uid;
	switch (_type)
	{
	case BulletType::_01:
		pBullet->~Bullet();
		new(pBullet) Bullet01{};
		break;
	case BulletType::_02:
		pBullet->~Bullet();
		new(pBullet) Bullet02{};
		break;
	case BulletType::_03:
		pBullet->~Bullet();
		new(pBullet) Bullet03{};
		break;
	case BulletType::_04:
		pBullet->~Bullet();
		new(pBullet) Bullet04{};
		break;
	case BulletType::_05:
		pBullet->~Bullet();
		new(pBullet) Bullet05{};
		break;
	case BulletType::_06:
		pBullet->~Bullet();
		new(pBullet) Bullet06{};
		break;
	}
	pBullet->uid = uid;
	pBullet->position = pos;
	pBullet->radian = rad;
	pBullet->bulletType = _type;
	pBullet->isAlias = _isAlias;
}

Bullet01::Bullet01()
{
	hp = 999;
	speed = 150;
	colliders.push_back(RECT{ -3,-3,3, 3 });
}

Bullet02::Bullet02()
{
	hp = 999;
	speed = 200;
	colliders.push_back(RECT{ -3,-3,3, 3 });
}

Bullet03::Bullet03()
{
	hp = 999;
	speed = 200;
	colliders.push_back(RECT{ -6,-6,6,6 });
}
void Bullet01::Update()
{
	Move();
	Bullet::Update();
}
void Bullet02::Update()
{
	radian += PI * 0.5f / 180;
	Move();
	Bullet::Update();
}
void Bullet03::Update()
{
	Move();
	Bullet::Update();
}
void Bullet01::Render()
{
	RenderManager::DrawCircle(RECT{ -6, -4, 6, 4 } +position, RGB(255, 130, 0), RGB(255, 0, 0));
}
void Bullet02::Render()
{
	RenderManager::DrawCircle(RECT{ -4, -4, 4, 4 } + position, RGB(255, 130, 0), RGB(255, 0, 0));
}

void Bullet03::Render()
{
	RenderManager::DrawCircle(RECT{ -8, -8, 8, 8 } + position, RGB(255, 130, 0), RGB(255, 0, 0));
}

Bullet04::Bullet04()
{
	hp = 999;
	speed = 800;
	colliders.push_back(RECT{ -15,-3,15,3 });
}

void Bullet04::Update()
{
	Move();
	Bullet::Update();
}

void Bullet04::Render()
{
	RenderManager::DrawCircle(RECT{ -30, -5, 30, 5 } + position, RGB(100, 200, 255), RGB(0, 0, 255));
}

Bullet05::Bullet05()
{
	hp = 999;
	speed = 500;
	colliders.push_back(RECT{ -4,-4,4,4 });
}

void Bullet05::Update()
{
	radian += PI * 1.f * 15.f / 180;
	position.x += speed * TimeManager::DeltaTime();
	position.y += 15.f * sinf(radian);
	Bullet::Update();
}

void Bullet05::Render()
{
	RenderManager::DrawCircle(RECT{ -5, -5, 5, 5 } + position, RGB(200, 100, 200), RGB(0, 0, 200));
}

Bullet06::Bullet06()
{
	hp = 999;
	speed = 200;
	colliders.push_back(RECT{ -4,-4,4,4 });
}

void Bullet06::Update()
{
	Transform direction;
	
	radian2 += PI * 1.f * 15.f / 180;
	direction.x += cosf(radian) +cosf(radian2);
	direction.y += sinf(radian) + sinf(radian2);
	position.x += direction.x * speed * TimeManager::DeltaTime();
	position.y += direction.y * speed * TimeManager::DeltaTime();
	Bullet::Update();
}

void Bullet06::Render()
{
	RenderManager::DrawCircle(RECT{ -5, -5, 5, 5 } +position, RGB(200, 100, 200), RGB(0, 0, 200));
}
