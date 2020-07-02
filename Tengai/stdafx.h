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

#include "Define.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "SceneManager.h"



extern HWND g_hwnd;

template<typename EnumT>
constexpr int ENUM_MAX()
{
	return (int)EnumT::END;
}