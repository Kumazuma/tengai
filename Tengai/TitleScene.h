#pragma once
#include "SceneManager.h"
class TitleScene : public IScene
{
	// IScene을(를) 통해 상속됨
	virtual void OnLoaded() override;
	virtual void OnUnloaded() override;
	virtual void Update() override;
};

