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
	//TODO: Pause
	//TODO: Resume
	bool isPause = false;
private:
	bool isShutdown = false;
	
};

