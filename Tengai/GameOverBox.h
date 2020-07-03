#pragma once
#include "UI.h"
class GameOverBox :
	public UI
{
private:
	GameOverBox();
	virtual ~GameOverBox();

public:
	static GameOverBox* GetInstance();
	static void Release();

	virtual void Update() override;
	virtual void Render() override;

	static void Show();
	static void Hide();
};

