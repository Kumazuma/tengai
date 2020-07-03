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
	int frameCounter = 0; // ������ ī����(�ʴ� ����)
	int targetFPS = 60; // ��ǥ ������
	int fps = 0; // ������ FPS (��¿�)
	float deltaTime = 0.f; // ��ŸŸ��
	int targetFrameRate = 0; // ������ �� ��ǥ ��� �ð�
	DWORD oldTime = 0; // ������ ���������� �ð�
	int timeStack = 0;  // �����Ӵ� �ʰ�/�̸� �ð�(����)
	DWORD elapseSum = 0; // 1�� ������

};

