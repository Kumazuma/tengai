#pragma once
#include"UI.h"
class GameWinBox :
	public UI
{
public:
	GameWinBox();
	virtual ~GameWinBox();
	virtual void Update() override;
	virtual void Render() override;

	void Show();
	void Hide();
};

