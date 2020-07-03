#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <windows.h>
// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <list>

using namespace std;

// ����� �߰�

#include "MemoryPool.h"
#include "Define.h"
#include "MainGame.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "EventManager.h"


extern HWND g_hwnd;

