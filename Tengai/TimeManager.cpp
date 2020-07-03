#include "stdafx.h"
#include "TimeManager.h"

TimeManager* pTimeManager = nullptr;

TimeManager::TimeManager()
{
}

TimeManager::~TimeManager()
{
	
}

TimeManager* TimeManager::GetInstance()
{
	if (pTimeManager == nullptr)
	{
		pTimeManager = new TimeManager();
	}
	return pTimeManager;
}

void TimeManager::Release()
{
	delete pTimeManager;
	pTimeManager = nullptr;
}

void TimeManager::SetFrame(int _framePerSec)
{
	if (_framePerSec < 0)return;
	pTimeManager->targetFPS = _framePerSec;
	pTimeManager->targetFrameRate = 1000 / _framePerSec;
}

bool TimeManager::SkipFrame()
{
	DWORD curTime = GetTickCount(); // 현재 측정 시간
	DWORD elapse; // 1프레임 경과시간 (ms)
	

	if (pTimeManager->oldTime == 0)
	{
		pTimeManager->oldTime = curTime;
		return false;
	}

	// 프레임당 걸린시간 ms
	elapse = curTime - pTimeManager->oldTime;
	pTimeManager->elapseSum += elapse;
	// 올드타임 갱신
	pTimeManager->oldTime = curTime;
	// 델타타임 갱신
	pTimeManager->deltaTime = (float)elapse / 1000;
	
	// 프레임 카운트
	pTimeManager->frameCounter++;

	if (pTimeManager->elapseSum >= 1000) // 1초 경과시
	{
		pTimeManager->fps = pTimeManager->frameCounter; // 출력용 fps세팅
		pTimeManager->frameCounter = 0; // 
		pTimeManager->elapseSum = 0;
	}

	// 프레임당 초과/미만 시간 
	pTimeManager->timeStack += elapse - pTimeManager->targetFrameRate;

	if (pTimeManager->timeStack >= pTimeManager->targetFrameRate) // 느리면
	{
		pTimeManager->timeStack -= pTimeManager->targetFrameRate;
		return true;
		
	}
	else if (pTimeManager->timeStack < pTimeManager->targetFrameRate) // 빠르면
	{
		Sleep(abs(pTimeManager->timeStack));
	}
		

	return false;
}

float TimeManager::DeltaTime()
{
	return pTimeManager->deltaTime;
}

int TimeManager::GetFPS()
{
	return pTimeManager->fps;
}

void TimeManager::RenderFPS()
{
	WCHAR wstr[8];
	wsprintf(wstr, L"%d", pTimeManager->fps);
	RenderManager::DrawString(wstr, 0, 0);
}
