#include "stdafx.h"
#include "Monster.h"
#include "RenderManager.h"

Monster::Monster() :
	initState{ this, Transform{400, -100} , Transform{450, 300 } , Transform{400, 500} },
	moveDownState{ this, Transform{400, 100} , Transform{550, 200 } , Transform{400, 500} },
	moveUpState{ this, Transform{400, 500} , Transform{250, 200 } , Transform{400, 100} },
	waitState{ 50 },
	waitState2{ 50 },
	fireState{this, 0.5f}
{
	this->type = ObjectType::MONSTER;
	this->pState = &initState;
	this->speed = 100;
	initState.pNextState = &waitState;
	waitState.pNextState = &moveUpState;
	moveUpState.pNextState = &waitState2;
	waitState2.pNextState = &moveDownState;
	moveDownState.pNextState = &waitState;
	this->pState->Reset();
}

void Monster::Update()
{
	auto pNextState = pState->Update();
	fireState.Update();
	if (pNextState != pState)
	{
		pState = pNextState;
		pNextState->Reset();
	}
}

void Monster::Render()
{
	RenderManager::DrawCircle(RECT{ 0, 0, 20, 20 } + position);
}
