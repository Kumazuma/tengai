#pragma once
#include "SceneManager.h"
class TitleScene : public IScene
{
	// IScene��(��) ���� ��ӵ�
	virtual void OnLoaded() override;
	virtual void OnUnloaded() override;
	virtual void Update() override;
};

