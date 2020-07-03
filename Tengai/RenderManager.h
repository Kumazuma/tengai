#pragma once
#include <Windows.h>
#include "D2DRenderManager.h"
using RenderManager = D2DRenderManager;
//class RenderManager
//{
//private:
//	RenderManager();
//	~RenderManager();
//
//public:
//	static RenderManager* GetInstance();
//
//	static void DrawRect(const RECT& _rc);
//	static void DrawCircle(const RECT& _rc);
//	static void DrawString(const WCHAR* _str,int _x, int _y);
//	static void Present();
//	static void Clear();
//
//private:
//	HDC hdc;
//	HBITMAP hBitmap;
//	HDC hBackBufferDC;
//	RECT area = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
//};
//
