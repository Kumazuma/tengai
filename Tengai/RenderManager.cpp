#include "stdafx.h"
#include "RenderManager.h"
//
//RenderManager* pRenderManager = nullptr;
//
//RenderManager::RenderManager()
//{
//	hdc = GetDC(g_hwnd);
//	hBitmap = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
//	hBackBufferDC = CreateCompatibleDC(hdc);
//	SelectObject(hBackBufferDC, hBitmap);
//}
//
//RenderManager::~RenderManager()
//{
//	ReleaseDC(g_hwnd, hdc);
//	//일단 해제해 주고
//	if (hBackBufferDC != nullptr)
//	{
//		SelectObject(hBackBufferDC, nullptr);
//		DeleteDC(hBackBufferDC);
//	}
//	//백버퍼도 지운다.
//	if (hBitmap != nullptr)
//	{
//		DeleteObject(hBitmap);
//	}
//}
//
//RenderManager * RenderManager::GetInstance()
//{
//	if (pRenderManager == nullptr)
//	{
//		pRenderManager = new RenderManager;
//	}
//	return pRenderManager;
//}
//
//void RenderManager::DrawRect(const RECT& _rc)
//{
//	Rectangle(pRenderManager->hBackBufferDC, _rc.left, _rc.top, _rc.right, _rc.bottom);
//}
//
//void RenderManager::DrawCircle(const RECT& _rc)
//{
//	Ellipse(pRenderManager->hBackBufferDC, _rc.left, _rc.top, _rc.right, _rc.bottom);
//}
//
//void RenderManager::DrawString(const WCHAR* _str, int _x, int _y)
//{
//	TextOutW(pRenderManager->hBackBufferDC, _x, _y, _str, wcslen(_str));
//}
//
//void RenderManager::Present()
//{
//	BitBlt(pRenderManager->hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
//		pRenderManager->hBackBufferDC, 0, 0, SRCCOPY);
//}
//
//void RenderManager::Clear()
//{
//	FillRect(pRenderManager->hBackBufferDC, &pRenderManager->area,
//		(HBRUSH)GetStockObject(WHITE_BRUSH));
//}
