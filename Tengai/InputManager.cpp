#include "stdafx.h"
#include "InputManager.h"

InputManager* pInputManager = nullptr;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

InputManager* InputManager::GetInstance()
{
	if (pInputManager == nullptr)
	{
		pInputManager = new InputManager();
	}

	return pInputManager;
}

void InputManager::Update()
{
	Clear();

	for (int i = 0; i < RANGE_OF_KEYS; i++)
	{
		SHORT keystate = GetAsyncKeyState(i);
		pInputManager->keys[i] = keystate & 0x8001;
		pInputManager->keyDowns[i] = keystate & 0x0001;
		pInputManager->keyUps[i] = keystate & 0x8000;
	}
	
}

void InputManager::Release()
{
	delete pInputManager;
	pInputManager = nullptr;
}

void InputManager::Clear()
{
	memset(pInputManager->keys, 0, RANGE_OF_KEYS);
	memset(pInputManager->keyDowns, 0, RANGE_OF_KEYS);
	memset(pInputManager->keyUps, 0, RANGE_OF_KEYS);
}

bool InputManager::GetKey(int _vkey)
{
	return pInputManager->keys[_vkey];
}

bool InputManager::GetKeyDown(int _vkey)
{
	return pInputManager->keyDowns[_vkey];
}

bool InputManager::GetKeyUp(int _vkey)
{
	return pInputManager->keyUps[_vkey];
}
