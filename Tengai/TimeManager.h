#pragma once
class TimeManager
{
private:
	TimeManager();
	~TimeManager();

public:
	static TimeManager* GetInstance();
	static void Release();
	static void SetFrame(int _framePerSec);
	static bool SkipFrame();
	static float DeltaTime();
	static int GetFPS();
	static void RenderFPS();

private:
	// Frame Control
	int frameCounter = 0; // 프레임 카운터(초당 갱신)
	int targetFPS = 60; // 목표 프레임
	int fps = 0; // 마지막 FPS (출력용)
	float deltaTime = 0.f; // 델타타임
	int targetFrameRate = 0; // 프레임 당 목표 경과 시간
	DWORD oldTime = 0; // 측정용 이전프레임 시간
	int timeStack = 0;  // 프레임당 초과/미만 시간(누산)
	DWORD elapseSum = 0; // 1초 측정용

};

