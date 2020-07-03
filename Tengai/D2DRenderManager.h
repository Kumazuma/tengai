#pragma once
#pragma once
#include <Windows.h>
#include "Define.h"
#include <d2d1.h>
#include <memory>
#include "dwrite.h"
//class D2DRenderManager
//{
//private:
//	D2DRenderManager();
//private:
//	void _DrawRect(const RECT& _rc);
//	void _DrawCircle(const RECT& _rc);
//	void _DrawString(const wchar_t* const _str, int _x, int _y);
//
//public:
//	~D2DRenderManager();
//	static const std::unique_ptr<D2DRenderManager>& GetInstance();
//
//	static void DrawRect(const RECT& _rc);
//	static void DrawCircle(const RECT& _rc);
//	static void DrawString(const WCHAR* _str, int _x, int _y);
//	//static void DrawSimpleCollider(const RECT& _rc, COLORREF _outlineColor);
//	static void Present();
//	static void Clear();
//
//private:
//	ID2D1HwndRenderTarget* pRenderTarget;
//	ID2D1SolidColorBrush* pBlackSolidBrush;
//	ID2D1SolidColorBrush* pWhiteSolidBrush;
//	IDWriteTextFormat* pWriteTextFormat;
//	IDWriteFactory* pWriteFactory;
//};
//
