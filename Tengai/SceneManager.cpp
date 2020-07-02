#include "stdafx.h"
#include "SceneManager.h"

SceneManager* pSceneManager = nullptr;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
	if (pSceneManager == nullptr)
	{
		pSceneManager = new SceneManager();
	}
	return pSceneManager;
}
