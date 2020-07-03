#pragma once


class MainGame
{
private:
	MainGame();
	~MainGame();

public:

	static MainGame* GetInstance();
	static void Initialize();
	static void Release();
	static void Run();
	static void Pause();
	static void Resume();
	static void Shutdown();

private:
	bool isShutdown = false;
	bool isPause = false;
};

