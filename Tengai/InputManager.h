#pragma once

#define RANGE_OF_KEYS 256

class InputManager
{
private:
	InputManager();
	~InputManager();

public:
	static InputManager* GetInstance();
	static void Update();
	static void Release();
	static void Clear();
	// 키 프레스
	static bool GetKey(int _vkey);
	// 키 다운
	static bool GetKeyDown(int _vkey);
	// 키 업
	static bool GetKeyUp(int _vkey);


private:
	bool keys[RANGE_OF_KEYS] = {};
	bool keyDowns[RANGE_OF_KEYS] = {};
	bool keyUps[RANGE_OF_KEYS] = {};
};

