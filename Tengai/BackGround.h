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

class Cloud : public UI
{
public:
	Cloud();
	virtual ~Cloud();
	virtual void Update() override;
	virtual void Render() override;
	
};

class Tree : public UI
{
public:
	Tree();
	virtual ~Tree();
	virtual void Update() override;
	virtual void Render() override;
};

