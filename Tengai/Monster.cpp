#include "stdafx.h"
#include "Monster.h"
#include "RenderManager.h"

Monster::Monster() 
{
	this->type = ObjectType::MONSTER;
	currentFireState = nullptr;
	currentMoveState = nullptr;
}
//우선 클리어
void Monster::Initialize(MonsterType monsterType, const Transform& firstPos)
{
	this->position = firstPos;
	for (auto it : fireStateList)
	{
		delete it;
	}
	fireStateList.clear();
	for (auto it : moveStateList)
	{
		delete it;
	}
	moveStateList.clear();
	switch (monsterType)
	{
	case MonsterType::MOB01:
	{
		//화면 아래에서 나타나서 화면 위로 사라지는 몬스터
		moveStateList.push_back(
			new BezierCurveMoveToState{ this, firstPos + Transform{0.f, 0.f} ,firstPos + Transform{-400, -1 * WINDOW_HEIGHT / 2 } ,firstPos + Transform{0,  -1 * WINDOW_HEIGHT} }
		);
		moveStateList.push_back(
			new DeleteState{ this }
		);
		fireStateList.push_back(
			new WaitState{ 0.1f });
		fireStateList.push_back(
			new FocusOnPlayerFireState{ this ,0.2f, 3.f });
		fireStateList.push_back(
			new WaitState{ 1 });
		speed = 100;
		moveStateList[0]->pNextState = moveStateList[1];

		fireStateList[0]->pNextState = fireStateList[1];
		fireStateList[1]->pNextState = fireStateList[2];
		fireStateList[2]->pNextState = fireStateList[0];
		monsterRect = RECT{ -18, -18, 18, 18 };
		colliders.push_back(RECT{ -16, -16, 16, 16 });
	}
	break;
	case MonsterType::MOB02:
	{
		//화면 오른쪽에서 나타나서 화면을 순회하는 몬스터
		moveStateList.push_back(
			new BezierCurveMoveToState{ this, firstPos + Transform{0.f, 0.f} ,firstPos + Transform{-200.f, -1.f * WINDOW_HEIGHT / 4 } ,firstPos + Transform{-400.f,  0.f} }
		);
		moveStateList.push_back(
			new BezierCurveMoveToState{ this, firstPos + Transform{-400.f, 0.f} ,firstPos + Transform{-150.f, 1.f * WINDOW_HEIGHT / 4 } ,firstPos + Transform{-100.f,  0.f} }
		);
		moveStateList.push_back(
			new BezierCurveMoveToState{ this, firstPos + Transform{-100.f, 0.f} ,firstPos + Transform{-150.f, -1.f * WINDOW_HEIGHT / 4 } ,firstPos + Transform{-400.f,  0.f} }
		);
		fireStateList.push_back(
			new WaitState{ 0.1f });
		fireStateList.push_back(
			new FlowerFireState{ this ,2.f, 6.f });
		fireStateList.push_back(
			new FocusOnPlayerFireState{ this, 0.2f, 3.f });
		speed = 100;
		moveStateList[0]->pNextState = moveStateList[1];
		moveStateList[1]->pNextState = moveStateList[2];
		moveStateList[2]->pNextState = moveStateList[1];

		fireStateList[0]->pNextState = fireStateList[1];
		fireStateList[1]->pNextState = fireStateList[2];
		fireStateList[2]->pNextState = fireStateList[1];

		monsterRect = RECT{ -28, -28, 28, 28 };
		colliders.push_back(RECT{ -24, -24, 24, 24 });
	}
	break;
	case MonsterType::BOSS:
		//화면 오른쪽에서 나타나서 화면을 순회하는 몬스터
		moveStateList.push_back(
			new BezierCurveMoveToState{ this, firstPos + Transform{0.f, 0.f} ,firstPos + Transform{-200.f, -1.f * WINDOW_HEIGHT / 4 } ,firstPos + Transform{-400.f,  0.f} }
		);
		moveStateList.push_back(
			new BezierCurveMoveToState{ this, firstPos + Transform{-400.f, 0.f} ,firstPos + Transform{-150.f, 1.f * WINDOW_HEIGHT / 4 } ,firstPos + Transform{-100.f,  0.f} }
		);
		moveStateList.push_back(
			new BezierCurveMoveToState{ this, firstPos + Transform{-100.f, 0.f} ,firstPos + Transform{-150.f, -1.f * WINDOW_HEIGHT / 4 } ,firstPos + Transform{-400.f,  0.f} }
		);
		fireStateList.push_back(
			new WaitState{ 0.1f });
		fireStateList.push_back(
			new FlowerFireState{ this ,2.f, 6.f });
		fireStateList.push_back(
			new FocusOnPlayerFireState{ this, 0.2f, 3.f });
		fireStateList.push_back(
			new FlowerCurvesFireState{ this, 0.2f, 3.f });
		fireStateList.push_back(
			new FocusOnPlayerFireState{ this, 0.2f, 3.f });
		speed = 50;
		moveStateList[0]->pNextState = moveStateList[1];
		moveStateList[1]->pNextState = moveStateList[2];
		moveStateList[2]->pNextState = moveStateList[1];

		fireStateList[0]->pNextState = fireStateList[1];
		fireStateList[1]->pNextState = fireStateList[2];
		fireStateList[2]->pNextState = fireStateList[3];
		fireStateList[3]->pNextState = fireStateList[4];
		fireStateList[4]->pNextState = fireStateList[1];

		monsterRect = RECT{ -36, -36, 36, 36 };
		colliders.push_back(RECT{ -32, -32, 32, 32 });
		
		break;
	}
	simpleCollider = CreateSimpleCollider(colliders);
	currentMoveState = this->moveStateList.front();
	currentFireState = this->fireStateList.front();
	currentMoveState->Reset();
	currentFireState->Reset();
}

Monster::~Monster()
{
	for (auto it : fireStateList)
	{
		delete it;
	}
	fireStateList.clear();
	for (auto it : moveStateList)
	{
		delete it;
	}
	moveStateList.clear();
}

void Monster::Update()
{
	if (currentMoveState != nullptr)
	{
		if (currentMoveState->Update())
		{
			auto pNext = currentMoveState->pNextState;
			if (pNext != nullptr)
			{
				pNext->Reset();
				currentMoveState = pNext;
			}
		}
	}
	if (currentFireState != nullptr)
	{
		if (currentFireState->Update())
		{
			auto pNext = currentFireState->pNextState;
			if (pNext != nullptr)
			{
				pNext->Reset();
				currentFireState = pNext;
			}
		}
	}
}

void Monster::Render()
{
	RenderManager::DrawRect(monsterRect + position);
}