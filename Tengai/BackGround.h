#pragma once
#include "UI.h"
class BackGround : public UI
{
private:
	BackGround();
	virtual ~BackGround();
public:
	static BackGround* GetInstance();
	static void Release();

	virtual void Update() override;
	virtual void Render() override;



};

